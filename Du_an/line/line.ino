const int sensorPins[5] = {A1, A2, A3, A4, A5}; // Từ trái sang phải: trái -> giữa -> phải
const int EnA = 3; const int EnB = 6;
const int InA = 2; const int InB = 4;
const int InC = 5; const int InD = 7;

float Kp = 25.0, Ki = 0.0, Kd = 15.0;
float error = 0, previousError = 0, integral = 0;

int baseSpeed = 150;
int weights[5] = {-2, -1, 0, 1, 2};

void setup() {
  for (int i = 0; i < 5; i++) pinMode(sensorPins[i], INPUT);
  pinMode(EnA, OUTPUT); pinMode(InA, OUTPUT); pinMode(InB, OUTPUT);
  pinMode(EnB, OUTPUT); pinMode(InC, OUTPUT); pinMode(InD, OUTPUT);
}

bool isOnLine(int pin) {
  return analogRead(pin) < 500; // IR tắt đèn → đang thấy line đen
}

bool onBlackSquare() {
  for (int i = 0; i < 5; i++) {
    if (!isOnLine(sensorPins[i])) return false;
  }
  return true; // tất cả IR tắt đèn → trên ô vuông đen
}

float readLineError() {
  int sum = 0, count = 0;
  for (int i = 0; i < 5; i++) {
    if (isOnLine(sensorPins[i])) {
      sum += weights[i];
      count++;
    }
  }
  if (count == 0) return 0;
  return (float)sum / count;
}

void setMotors(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(EnA, leftSpeed);
  analogWrite(EnB, rightSpeed);

  digitalWrite(InA, LOW); digitalWrite(InB, HIGH); // motor trái
  digitalWrite(InC, LOW); digitalWrite(InD, HIGH); // motor phải
}

void loop() {
  if (onBlackSquare()) {
    analogWrite(EnA, 0);
    analogWrite(EnB, 0);
    return;
  }

  bool leftIR = isOnLine(sensorPins[0]);
  bool rightIR = isOnLine(sensorPins[4]);
  bool centerIR = isOnLine(sensorPins[2]);

  if (centerIR) {
    // IR giữa đang thấy line ⇒ xe đi thẳng
    setMotors(baseSpeed, baseSpeed);
  } else if (leftIR || rightIR) {
    // Nếu trái/phải thấy line ⇒ xử lý PID để quay về giữa
    error = readLineError();
    integral += error;
    float derivative = error - previousError;
    float pid = Kp * error + Ki * integral + Kd * derivative;

    int left = baseSpeed + pid;
    int right = baseSpeed - pid;

    setMotors(left, right);
    previousError = error;
  } else {
    // Không cảm biến nào thấy line ⇒ dừng hoặc xử lý mất line
    analogWrite(EnA, 0);
    analogWrite(EnB, 0);
  }

  delay(10);
}
