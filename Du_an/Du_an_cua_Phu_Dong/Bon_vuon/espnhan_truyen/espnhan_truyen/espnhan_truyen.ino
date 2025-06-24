/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL8w3ey7vp"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "5vCMCSj1DO9pTbBZYQo8mz0zNeUnhzaU"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Phuc Hung";
char pass[] = "PH777777777";
#include <Wire.h>

void setup() {
  Serial.begin(9600); /* begin serial for debug */
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

int value[16] = {0};

BLYNK_WRITE(V0) { // tien lui xe
  byte nhan = param.asInt();
  if(nhan > 3){
    value[0] = 1;
    switch (nhan){
      case 4:
        value[1] = 0;
        value[2] = 1;
        break;
      case 5:
        value[1] = 1;
        value[2] = 0;
        break;
      case 6:
        value[1] = 1;
        value[2] = 1;
        break;
    }
  } else if (nhan <= 3){
    value[0] = 0;
    switch (nhan){
      case 2:
        value[1] = 0;
        value[2] = 1;
        break;
      case 1:
        value[1] = 1;
        value[2] = 0;
        break;
      case 0:
        value[1] = 1;
        value[2] = 1;
        break;
      default:
        value[1] = 0;
        value[2] = 0;
        break;
    }
  }
}
BLYNK_WRITE(V1) { // trai phai xe
  byte nhan = param.asInt();
  if(nhan > 3){
    value[3] = 1;
    switch (nhan){
      case 4:
        value[4] = 0;
        value[5] = 1;
        break;
      case 5:
        value[4] = 1;
        value[5] = 0;
        break;
      case 6:
        value[4] = 1;
        value[5] = 1;
        break;
    }
  } else if (nhan <= 3){
    value[3] = 0;
    switch (nhan){
      case 2:
        value[4] = 0;
        value[5] = 1;
        break;
      case 1:
        value[4] = 1;
        value[5] = 0;
        break;
      case 0:
        value[4] = 1;
        value[5] = 1;
        break;
      default:
        value[4] = 0;
        value[5] = 0;
        break;
    }
  }
}
BLYNK_WRITE(V2) { // trai phai cam
  int nhan = param.asInt();
  if(nhan == 3){
    value[12] = 0;
    value[13] = 1;
  } else if(nhan == 1){
    value[12] = 1;
    value[13] = 0;
  } else {
    value[12] = 0;
    value[13] = 0;
  }
}
BLYNK_WRITE(V3) { // len xuong cam
  int nhan = param.asInt();
  if(nhan == 3){
    value[15] = 0;
    value[14] = 1;
  } else if(nhan == 1){
    value[15] = 1;
    value[14] = 0;
  } else {
    value[15] = 0;
    value[14] = 0;
  }
}
BLYNK_WRITE(V4) { // thoi phan
  value[10] = param.asInt();
}
BLYNK_WRITE(V5) { // nhan phan
  value[11] = param.asInt();
}
BLYNK_WRITE(V6) { // phun
  value[9] = param.asInt();
}
BLYNK_WRITE(V7) { // cat
  value[6] = param.asInt();
}
BLYNK_WRITE(V8) { // nang cat
  value[7] = param.asInt();
}
BLYNK_WRITE(V9) { // ha cat
  value[8] = param.asInt();
}

void loop() {
  Blynk.run();
  Wire.beginTransmission(8); /* begin with device address 8 */
  for (int i = 0; i < 16; i++){
    Serial.print(value[i]);
    Wire.write(value[i]);
  }
  Serial.println();
  Wire.endTransmission(); /* stop transmitting */
  delay(10);
}