#include <Servo.h>

//----- khai bao cac chan
#define IR 12
#define Mp A4
#define Fi 13
#define trig1 A0
#define trig2 A2
#define echo1 A1
#define echo2 A3
#define UV A5
int sin1 = 2, sin2 = 3, sin3 = 4, sin4 = 7, din1 = 8, din2 = 9, din3 = 10, din4 = 11;
//sin dung cho speaker, din dung cho dc
//----- ket thuc khai bao

Servo ser1;
Servo ser2;

void setup() {
  ser1.attach(5);
  ser2.attach(6);

  ser1.write(0);
  ser2.write(0);

  for (int i = 2; i <= 13; i++) {
    if (i != 5 && i != 6) {
      if (i == 12 || i == 13) pinMode(i, INPUT);
      else pinMode(i, OUTPUT);
    }
  }

  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);  
}

//----- bom
void bom() {
  digitalWrite(din1, 1);
  digitalWrite(din2, 1);
  delay(1500);
  digitalWrite(din1, 0);
  digitalWrite(din2, 0);
}

//----- quay
void quay() {
  digitalWrite(din3, 1);
  digitalWrite(din4, 1);
  delay(5000);
  digitalWrite(din3, 0);
  digitalWrite(din4, 0);
}

//----- bat loa
void loa_on() {
  digitalWrite(sin1, 1);
  digitalWrite(sin2, 1);
}

//----- tat loa
void loa_off() {
  digitalWrite(sin1, 0);
  digitalWrite(sin2, 0);
}

//----- bat coi
void coi_on() {
  digitalWrite(sin3, 1);
  digitalWrite(sin4, 1);
}

//----- tat coi
void coi_off() {
  digitalWrite(sin3, 0);
  digitalWrite(sin4, 0);
}

//----- sieu am 1
int hc1() {
  int dura;
  int dis;

  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(5);
  digitalWrite(trig1, 0);

  dura = pulseIn(echo1, 1);
  dis = int(dura / 2 / 29.412);

  return dis;
}

//----- sieu am 2
int hc2() {
  int dura;
  int dis;

  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(5);
  digitalWrite(trig2, 0);

  dura = pulseIn(echo2, 1);
  dis = int(dura / 2 / 29.412);

  return dis;
}

// bien kiem tra thoi gian cho 
long long spo = 0, spo2 = 0;
bool sta = 0;
//

void loop() {
  // hc1 dieu khien servo
  // hc2 dieu khien dong co
  digitalWrite(UV, 1);

  //--- hong ngoai bom
  if (digitalRead(IR) == 1) {
    bom();
  }

  //--- sieu am 1 servo quay
  if (hc1() <= 5) {
    digitalWrite(UV, 0);
    loa_on();
    
    ser1.write(180);
    ser2.write(180);
    delay(2000);
    ser1.write(0);
    ser2.write(0);

    loa_off();
    digitalWrite(UV, 1);
  }else loa_off;

  //--- sieu am 2 quay dong co
  if((hc2() <= 10) != sta){
    spo = millis();
    sta = 1;
  }

  if(millis()-spo >= 10000){
    quay();
    sta = 0;
  }

  //--- khoi lua bat coi
  if(digitalRead(Mp) == 1 || digitalRead(Fi) == 1){
    coi_on();
  }else coi_off;
}
