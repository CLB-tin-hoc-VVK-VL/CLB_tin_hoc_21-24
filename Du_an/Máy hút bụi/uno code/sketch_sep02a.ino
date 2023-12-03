#include <AFMotor.h>
AF_DCMotor may1(2), may2(1);

const int toc_do = 80;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
  may1.setSpeed(toc_do);
  may2.setSpeed(toc_do);
  may1.run(RELEASE);
  may2.run(RELEASE);
}

void loop() {
  int x = 0, y = 0, z = 0;
  x = digitalRead(A1), y = digitalRead(A2), z = digitalRead(A3);
  may1.setSpeed(toc_do);
  may2.setSpeed(toc_do);
  if ((x == 1) && (y == 1) && (z == 1)) {
    Serial.println("tien");
    may1.run(FORWARD);
    may2.run(FORWARD);
  }
  else if ((x == 0) && (y == 1) && (z == 0)) {
    Serial.println("lui");
    may1.run(BACKWARD);
    may2.run(BACKWARD);
  }
  else if ((x == 1) && (y == 1) && (z == 0)) {
    Serial.println("trai");
    may1.run(FORWARD);
    may2.run(RELEASE);
  }
  else if ((x == 0) && (y == 1) && (z == 1)) {
    Serial.println("phai");
    may1.run(RELEASE);
    may2.run(FORWARD);
  }
  else if ((x == 0) && (y == 0) && (z == 0)) {
    Serial.println("dung");
    may1.run(RELEASE);
    may2.run(RELEASE);
  }
}
