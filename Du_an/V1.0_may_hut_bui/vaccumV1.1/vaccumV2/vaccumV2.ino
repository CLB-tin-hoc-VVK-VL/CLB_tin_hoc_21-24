/* mart vaccum cleaner V2
This program use for UNO R3 board

Units:
- Moving: L298 (left = 1-2, right = 3-4)
- Cleaner: relay
- Sensor: switch, IR

pin map:
- L298: 4 -> 8
- relay: 9
- IR: 10 -> 13   b:true = 1, false = 0 --      
- switch: A0 -> A5    (true = 0,  = 1)

*/

// Declare pin for L298
const byte in1 = 4;
const byte in2 = 6;
const byte in3 = 7;
const byte in4 = 8;
const byte pwm = 5;

// Declare relay
#define fan A5

// Declare switch
#define signal_switch_left1 3     //A0
#define signal_switch_left2 2     //A1
#define signal_switch_middle1 A0  //A2
#define signal_switch_middle2 A1  //A3
#define signal_switch_right1 A3   //2
#define signal_switch_right2 A2   //3

// Declare IR
const byte signal_IR_left = 10;    //10;
const byte signal_IR_middle = 12;  //11;
const byte signal_IR_right = 11;   //12;
const byte signal_IR_behind = 13;

// Limited time (milisecond)
const int turn_half = 200;
const int turn_full = 300;
const int back = 500;

// previod turning
char p_turn = 'l';

// time processing
long long s_time = millis();

// setup
void setup() {
  // setup pin
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A5, OUTPUT);

  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  digitalWrite(fan, 0);
  // Display unit
  Serial.begin(9600);
}

// Moving unit
void forward(byte speed = 255) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);

  digitalWrite(in3, 1);
  digitalWrite(in4, 0);

  analogWrite(pwm, speed);
}

void backward(byte speed = 255) {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);

  digitalWrite(in3, 0);
  digitalWrite(in4, 1);

  analogWrite(pwm, speed);
}

void turnleft(byte speed = 150) {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);

  digitalWrite(in3, 1);
  digitalWrite(in4, 0);

  analogWrite(pwm, speed);
}

void turnright(byte speed = 150) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);

  digitalWrite(in3, 0);
  digitalWrite(in4, 1);

  analogWrite(pwm, speed);
}

void stop(byte speed = 0) {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);

  digitalWrite(in3, 0);
  digitalWrite(in4, 0);

  analogWrite(pwm, speed);
}

// making delay
void DELAY(int time) {
  for (int n = 0; n < time; n++) {
    delay(1);
    if (digitalRead(signal_switch_left1) == 0 || digitalRead(signal_switch_left2) == 0 || digitalRead(signal_switch_right1) == 0 || digitalRead(signal_switch_right2) == 0 || digitalRead(signal_switch_middle1) == 0 || digitalRead(signal_switch_middle2) == 0 || digitalRead(signal_IR_left) == 1 || digitalRead(signal_IR_middle) == 1 || digitalRead(signal_IR_right) == 1 || digitalRead(signal_IR_behind) == 1) {
      break;
    }
    Serial.println(n);
  }
  // delay(turn_full);
  stop();
}

char get_signal() {
  if (digitalRead(signal_switch_left1) == 0 || digitalRead(signal_switch_left2) == 0 || digitalRead(signal_IR_left) == 1) {
     return 'l';
  } else if (digitalRead(signal_switch_middle1) == 0 || digitalRead(signal_switch_middle2) == 0 || digitalRead(signal_IR_middle) == 1) {
     return 'm';
  } else if (digitalRead(signal_switch_right1) == 0 || digitalRead(signal_switch_right2) == 0 || digitalRead(signal_IR_right) == 1) {
     return 'r';
  } else if (digitalRead(signal_IR_behind) == 1){
    return 'b';
  }else {
    return 'n';
  }
}

// main
void loop() {
  if (millis() - s_time < 1800000) {
    digitalWrite(fan, 1);
    char result = get_signal();
    Serial.println(result);
    if (result == 'l') {
      backward();
      DELAY(turn_half);
      turnright();
      DELAY(turn_full);
      p_turn = 'r';
    } else if (result == 'r') {
      backward();
      DELAY(turn_half);
      turnleft();
      p_turn = 'l';
      DELAY(turn_full);
    } else if (result == 'm') {
      backward();
      DELAY(turn_half);
      if (p_turn == 'l') {
        turnright();
        p_turn = 'r';
      } else if (p_turn = 'r') {
        turnleft();
        p_turn = 'l';
      }
      DELAY(turn_full);
    } else if(result == 'b'){
      forward();
      DELAY(turn_half);
      if (p_turn == 'r') {
        turnright();
        p_turn = 'r';
      } else if (p_turn = 'l') {
        turnleft();
        p_turn = 'l';
      }
      DELAY(turn_full);
    }else {
      forward();
    }
  } else {
    digitalWrite(fan, 0);
    stop();
    delay(1000000);
    s_time = millis();
  }
}
