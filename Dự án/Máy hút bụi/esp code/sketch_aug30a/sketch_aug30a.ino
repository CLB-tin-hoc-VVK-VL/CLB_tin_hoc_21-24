#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>;

SimpleTimer timer;

// thong tin
char auth[] = "hHcEtg5aFhtb2bmTh5yaqF5EKDv7_27u";
char ssid[] = "PHONG TIN HOC";
char pass[] = "123456789a";

// bien
int x = 128, y = 128;

// nhan gia tri tu blynk
BLYNK_WRITE(V2) {
  y = param.asInt();
}

BLYNK_WRITE(V0) {
  x = param.asInt();
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(5, 1);
  digitalWrite(4, 0);
  digitalWrite(0, 1);
}

void loop()
{
  Blynk.run();
  timer.run();
  Serial.print(x);
  Serial.print(",   ");
  Serial.println(y);
  //trai
  if (((37.5 < y) && (y < 218.5))) {
    if ((0 <= x) && (x <= 37.5)) {
      Serial.println("trai");
      digitalWrite(5, 1);
      digitalWrite(4, 1);
      digitalWrite(0, 0);
    }//phai   
    else if ((218.5 <= x) && (x <= 255)) {
      Serial.println("phai");
      digitalWrite(5, 0);
      digitalWrite(4, 1);
      digitalWrite(0, 1);
    }
  }//tien
  else if ((37.5 <= x) && (x <= 218.5)) {
    if ((218.5 <= y) && (y <= 255)) {
      Serial.println("tien");
      digitalWrite(5, 1);
      digitalWrite(4, 1);
      digitalWrite(0, 1);
    }//lui
    else if ((0 <= y) && (y <= 37.5)) {
      Serial.println("lui");
      digitalWrite(5, 0);
      digitalWrite(4, 1);
      digitalWrite(0, 0);
    }
  }//dung
  int a = ((37.5 < x && x < 218.5) && (37.5 < y && y < 218.5));
  if (a) {
    Serial.println("dung");
    digitalWrite(5, 0);
    digitalWrite(4, 0);
    digitalWrite(0, 0);
  }
}
