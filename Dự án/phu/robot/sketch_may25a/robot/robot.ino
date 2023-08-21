//----------thu vien//----------
#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//----------dinh nghia//----------
#define SERVOMIN 90
#define SERVOMAX 600

//----------khoi tao//----------
Adafruit_PWMServoDriver mod_1 = Adafruit_PWMServoDriver(0x40);
Servo myservo;

//----------tao bien//----------
const int trig = 6;     // chân trig của SRF-05.
const int echo = 5;     // chân echo của SRF-05.

int tien1 = 10;         // chân IN - A của Module L298.
int tien2 = 11;         // chân IN - C của Module L298.
int lui1 = 12;          // chân IN - D của Module L298.
int lui2 = 13;          // chân IN - B của Module L298.
int dongcoservo = 9;    // chân Orange của Servo.

int gioihan = 25;
int i;
int x = 0;
unsigned long thoigian; // biến đo thời gian
int khoangcach;           // biến lưu khoảng cách
int khoangcachtrai, khoangcachphai;

int tong;
int a = 0;

int pos = 0;    // variable to store the servo position

int dau = 0;
int tayt = 1;
int tayp = 2;
int canhtayp = 3;
int canhtayt = 4;
int chant = 5;
int chanp = 6;
int banchant = 7;
int banchanp = 8;
int cotayp = 9;
int cotayt = 10;

int pos_dau = 91;
int pos_tayt = 180;
int pos_tayp = 0;
int pos_canhtayp = 90;
int pos_canhtayt = 90;
int pos_chant = 100;
int pos_chanp = 50;
int pos_banchant = 83;
int pos_banchanp = 90;
int pos_cotay = 90;

//----------chuong trinh con//----------
void dithang()
{


  digitalWrite(tien1, HIGH);
  digitalWrite(tien2, HIGH);
  //delay(2);

}

void disangtrai()
{
  resetdongco();
  digitalWrite(lui1, HIGH);
  delay(250);
  digitalWrite(lui1, LOW);


}
void disangphai()
{
  resetdongco();
  digitalWrite(lui2, HIGH);
  delay(250);
  digitalWrite(lui2, LOW);

}

void dilui()
{
  resetdongco();
  for (i = 0; i < 20; i++)

    digitalWrite(lui1, HIGH);
  digitalWrite(lui2, HIGH);
  delay(700);

  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}

void resetdongco()
{
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}
void dokhoangcach()
{
  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(10);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  thoigian = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  khoangcach = int(thoigian / 2 / 29.412);


}
void quaycbsangtrai()
{
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void quaycbsangphai()
{
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void resetservo()
{
  myservo.write(90);
}
int topulse(int goc)
{
  int xung = map(goc, 0, 180, SERVOMIN, SERVOMAX);
  return xung;
}
void reset() {
  mod_1.setPWM(dau, 0, topulse(pos_dau));            //4096
  mod_1.setPWM(tayt, 0, topulse(pos_tayt));          //4096
  mod_1.setPWM(tayp, 0, topulse(pos_tayp));          //4096
  mod_1.setPWM(canhtayt, 0, topulse(pos_canhtayt));  //4096
  mod_1.setPWM(canhtayp, 0, topulse(pos_canhtayp));  //4096
  mod_1.setPWM(chant, 0, topulse(pos_chant));        //4096
  mod_1.setPWM(chanp, 0, topulse(pos_chanp));        //4096
  mod_1.setPWM(banchant, 0, topulse(pos_banchant));   //4096
  mod_1.setPWM(banchanp, 0, topulse(pos_banchanp));   //4096
  mod_1.setPWM(cotayp, 0, topulse(pos_cotay));       //4096
  mod_1.setPWM(cotayt, 0, topulse(pos_cotay));       //4096
}

void sayhi() {
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayp, 0, topulse(pos_tayp + goc));  //4096
    delay(10);
  }
  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayp, 0, topulse(90 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayp, 0, topulse(50 + i));   //4096
    delay(10);
  }

  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayp, 0, topulse(90 + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayp, 0, topulse(130 - i));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayp, 0, topulse(180 - goc));  //4096
    delay(10);
  }
}

void dieunhay1() {
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(pos_tayt - goc));  //4096
    mod_1.setPWM(tayp, 0, topulse(pos_tayp + goc));  //4096
    delay(10);
  }
  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(90 + i));  //4096
    mod_1.setPWM(canhtayp, 0, topulse(90 - i));  //4096
    delay(10);
  }

  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(130 - i));  //4096
    mod_1.setPWM(canhtayp, 0, topulse(50 + i));   //4096
    delay(10);
  }

  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(90 - i));  //4096
    mod_1.setPWM(canhtayp, 0, topulse(90 + i));  //4096
    delay(10);
  }

  for (int i = 0; i < 40; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(50 + i));   //4096
    mod_1.setPWM(canhtayp, 0, topulse(130 - i));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(0 + goc));    //4096
    mod_1.setPWM(tayp, 0, topulse(180 - goc));  //4096
    delay(10);
  }
  for (int i = 0; i < 45; i++) {
    mod_1.setPWM(dau, 0, topulse(pos_dau + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 45; i++) {
    mod_1.setPWM(dau, 0, topulse(135 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 45; i++) {
    mod_1.setPWM(dau, 0, topulse(90 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 45; i++) {
    mod_1.setPWM(dau, 0, topulse(35 + i));  //4096
    delay(10);
  }
}

void dieunhay2() {
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(pos_tayt - goc));  //4096
    delay(10);
  }
  for (int i = 0; i < 66; i++) {
    mod_1.setPWM(dau, 0, topulse(pos_dau + i));  //4096
    mod_1.setPWM(cotayp, 0, topulse(90 + i));    //4096
    mod_1.setPWM(cotayt, 0, topulse(90 - i));    //4096
    delay(10);
  }
  for (int i = 0; i < 66; i++) {
    mod_1.setPWM(dau, 0, topulse(156 - i));     //4096
    mod_1.setPWM(cotayt, 0, topulse(35 + i));   //4096
    mod_1.setPWM(cotayp, 0, topulse(155 - i));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(0 + goc));         //4096
    mod_1.setPWM(tayp, 0, topulse(pos_tayp + goc));  //4096
    delay(10);
  }

  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(dau, 0, topulse(pos_dau - i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(90 - i));    //4096
    mod_1.setPWM(cotayp, 0, topulse(90 + i));    //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(dau, 0, topulse(36 + i));      //4096
    mod_1.setPWM(cotayt, 0, topulse(35 + i));   //4096
    mod_1.setPWM(cotayp, 0, topulse(155 - i));  //4096
    delay(10);
  }

  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayp, 0, topulse(180 - goc));  //4096
    delay(10);
  }
}

void dieunhay3() {
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayp, 0, topulse(0 + goc));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(pos_tayt - goc));  //4096
    mod_1.setPWM(tayp, 0, topulse(180 - goc));       //4096
    mod_1.setPWM(dau, 0, topulse(pos_dau + goc));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayt, 0, topulse(0 + goc));         //4096
    mod_1.setPWM(tayp, 0, topulse(pos_tayp + goc));  //4096
    mod_1.setPWM(dau, 0, topulse(180 - goc));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 92; goc++) {
    mod_1.setPWM(dau, 0, topulse(0 + goc));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 180; goc++) {
    mod_1.setPWM(tayp, 0, topulse(180 - goc));  //4096
    delay(10);
  }
}

void dieunhay4() {
  for (int goc = 0; goc < 100; goc++) {
    mod_1.setPWM(tayt, 0, topulse(pos_tayt - goc));  //4096
    mod_1.setPWM(tayp, 0, topulse(pos_tayp + goc));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(90 - i));  //4096
    mod_1.setPWM(canhtayp, 0, topulse(90 + i));  //4096
    delay(10);
  }

  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(90 - i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(90 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(35 + i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(35 + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(90 + i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(90 + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(155 - i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(155 - i));  //4096
    delay(10);
  }

  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(90 - i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(90 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(35 + i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(35 + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(90 + i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(90 + i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(cotayp, 0, topulse(155 - i));  //4096
    mod_1.setPWM(cotayt, 0, topulse(155 - i));  //4096
    delay(10);
  }
  for (int i = 0; i < 65; i++) {
    mod_1.setPWM(canhtayt, 0, topulse(35 + i));   //4096
    mod_1.setPWM(canhtayp, 0, topulse(155 - i));  //4096
    delay(10);
  }
  for (int goc = 0; goc < 100; goc++) {
    mod_1.setPWM(tayt, 0, topulse(80 + goc));   //4096
    mod_1.setPWM(tayp, 0, topulse(100 - goc));  //4096
    delay(10);
  }
}

void dieunhay5() {
  for (int i = 0; i <= 30; i++) {
    mod_1.setPWM(banchant, 0, topulse(83 - i));  //4096
    mod_1.setPWM(banchanp, 0, topulse(90 - i));  //4096
    mod_1.setPWM(dau, 0, topulse(pos_dau + i));  //4096
    delay(30);
  }
  delay(500);
  for (int i = 0; i <= 30; i++) {
    mod_1.setPWM(banchant, 0, topulse(53 + i));  //4096
    mod_1.setPWM(banchanp, 0, topulse(60 + i));  //4096
    mod_1.setPWM(dau, 0, topulse(116 - i));  //4096
    delay(30);
  }
  delay(500);
  for (int i = 0; i <= 30; i++) {
    mod_1.setPWM(banchant, 0, topulse(83 + i));  //4096
    mod_1.setPWM(banchanp, 0, topulse(90 + i));  //4096
    mod_1.setPWM(dau, 0, topulse(pos_dau - i));  //4096
    delay(30);
  }
  delay(500);
  for (int i = 0; i <= 30; i++) {
    mod_1.setPWM(banchant, 0, topulse(113 - i));  //4096
    mod_1.setPWM(banchanp, 0, topulse(120 - i));  //4096
    mod_1.setPWM(dau, 0, topulse(66 + i));  //4096
    delay(30);
  }
  delay(500);
}

//----------thiet lap//----------
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  mod_1.begin();
  mod_1.setOscillatorFrequency(27000000);
  mod_1.setPWMFreq(60);
  reset();
  delay(3000);
  sayhi();

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);   // chân echo sẽ nhận tín hiệu

  pinMode(tien1, OUTPUT);
  pinMode(tien2, OUTPUT);
  pinMode(lui1, OUTPUT);
  pinMode(lui2, OUTPUT);
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui1, LOW);
  // Serial.begin(9600);
  myservo.write(90);
  delay(500);
}

//----------vong lap//----------
void loop() {
  khoangcach = 0;
  dokhoangcach();
  if (khoangcach > gioihan || khoangcach == 0)
  {
    dokhoangcach();
    if (khoangcach > gioihan || khoangcach == 0)
    {
      dithang();
    }
  }
  else
  {

    resetdongco();
    quaycbsangtrai();

    khoangcachtrai = khoangcach;

    quaycbsangphai();
    khoangcachphai = khoangcach;
    if (khoangcachphai < 10 && khoangcachtrai < 10) {
      dilui();
    }
    else
    {
      if (khoangcachphai > khoangcachtrai)
      {
        disangtrai();
        delay(500);
      }
      if (khoangcachphai < khoangcachtrai)
      {
        disangphai();
        delay(500);
      }
    }
  }

  int a = digitalRead(8);
  if ( a == 0) {
    dieunhay1();
    delay(500);
    dieunhay2();
    delay(500);
    dieunhay3();
    delay(500);
    dieunhay4();
    delay(500);
    dieunhay5();
    delay(500);

  }
}
