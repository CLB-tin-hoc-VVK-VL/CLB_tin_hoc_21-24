/*
tao lenh dieu khien hoat dong 16 bit voi cac bit dieu khien mot chuc nang

1:1 bit dieu khien tien (0) va lui (1)
2:3 bit dieu khien truc x
4:1 bit dieu khien tien (0) va lui (1)
5:3 bit dieu khien truc y tien
8:1 bit dieu khien cat
9:1 bit dieu khien gian cat nang
10:1 bit dieu khien gian cat ha
11:1 bit dieu khien phun
12:1 bit dieu khien rai phan
13:1 bit quay trai servo
14:1 bit quay phai servo
15:1 bit bat / tat nha phan

0 123 4 567 8 9 10  11  12  13  14  15
0 000 0 000 0 0 0   0   0   0   0   0
 
di chuyen 1  (trai)
D13 - LPWM1
D12 - RPWM1
D11 - PWM1

di chuyen 2  (phai)
D10 - PWM2
D9 - RPWM2
D8 - LPWM2

nang / ha cat + bat tat quat phan
D7 - in2
D6 - in1
D5 - PWMA
D23 - in3
D24 - in4
pwmb khong dung

cat
D4 - relay cat

phun
D3 - relay phun

phan
D2 - relay quat

nha phan
D22 - relay nha

nrf - mega:
48 - csn
49 - ce
50 - miso
51 - mosi
52 - sck

step motor
D25 dirpin
D26 step pin
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(49, 48);               // CE, CSN
const byte address[6] = "00001";  //address through which two modules communicate.
#define tocdo0 0
#define tocdo1 85
#define tocdo2 170
#define tocdo3 255

#define quat_phan 2
#define phun 3
#define cat 4
#define pwma 5
#define in1 6
#define in2 7
#define lpwm2 8
#define rpwm2 9
#define pwm2 10
#define pwm1 11
#define rpwm1 12
#define lpwm1 13

#define nha_phan 22
#define in3 23
#define in4 24

// ket noi voi driver a4988
#define dirpin 25
#define steppin 26

void setup() {
  //----------set up address and check for connection
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  //----------done


  // set up for pin
  for(int i = 2; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
  for(int j = 22; j <= 26; j++){
    pinMode(j , OUTPUT);
  }
  // --------
}


// nhan du lieu tu remote
byte* receive_data() {
  byte info[32] = { 0 };
  radio.read(&info, sizeof(info));
  return info;
}


void tien(int tocdo){
  analogWrite(pwm1, tocdo);
  analogWrite(pwm2, tocdo);
  digitalWrite(lpwm1, 1);
  digitalWrite(lpwm2, 1);
  digitalWrite(rpwm1, 0);
  digitalWrite(rpwm2, 0);
}


void lui(int tocdo){
  analogWrite(pwm1, tocdo);
  analogWrite(pwm2, tocdo);
  digitalWrite(lpwm1, 0);
  digitalWrite(lpwm2, 0);
  digitalWrite(rpwm1, 1);
  digitalWrite(rpwm2, 1);
}


void dung(int tocdo){
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  digitalWrite(lpwm1, 1);
  digitalWrite(lpwm2, 1);
  digitalWrite(rpwm1, 1);
  digitalWrite(rpwm2, 1);
}


void trai(int tocdo){
  analogWrite(pwm1, 0);
  analogWrite(pwm2, tocdo);
  digitalWrite(lpwm1, 1);
  digitalWrite(lpwm2, 1);
  digitalWrite(rpwm1, 1);
  digitalWrite(rpwm2, 0);
}


void phai(int tocdo){
  analogWrite(pwm1, tocdo);
  analogWrite(pwm2, 0);
  digitalWrite(lpwm1, 1);
  digitalWrite(lpwm2, 1);
  digitalWrite(rpwm1, 0);
  digitalWrite(rpwm2, 1);
}


void nang_cat(int tocdo = 175){
  analogWrite(pwma, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
}


void ha_cat(int tocdo = 175){
  analogWrite(pwma, tocdo);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
}


void dung_ha(int tocdo = 0){
  analogWrite(pwma, 0);
  digitalWrite(in1, 1);
  digitalWrite(in2, 1);
}


void cat_co(){
  digitalWrite(cat, 1);
}

void dung_cat_co(){
  digitalWrite(cat, 0);
}


void phun_thuoc(){
  digitalWrite(phun, 1);
}

void dung_phun_thuoc(){
  digitalWrite(phun, 0);
}


void bat_quat(){
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}


void tat_quat(){
  digitalWrite(in3, 1);
  digitalWrite(in4, 1);
}


void rai_phan(){
  digitalWrite(nha_phan, 1);
}

void dung_rai(){
  digitalWrite(nha_phan, 0);
}


//dieu khien stepmotor
void xoay_sang_trai(int tocdo = 1000){
  digitalWrite(dirpin, 0);
  for(int x = 0; x < 10; x++){
    digitalWrite(steppin, 1);
    delayMicroseconds(tocdo);
    digitalWrite(steppin, 0);
    delayMicroseconds(tocdo);
  }
}

void xoay_sang_phai(int tocdo = 1000){
  digitalWrite(dirpin, 1);
  for(int x = 0; x < 10; x++){
    digitalWrite(steppin, 1);
    delayMicroseconds(tocdo);
    digitalWrite(steppin, 0);
    delayMicroseconds(tocdo);
  }
}

void dung_xoay(){
  digitalWrite(dirpin, 0);
  digitalWrite(steppin, 0);
}


byte* control; // luu du lieu dieu khien


void loop() {
  //Read the data if available in buffer
  if (radio.available()) {
    control = receive_data();
  }


  // doc du lieu dieu khien di chuyen
  if(control[0] == 0){
    if(control[1] == 1 && control[2] == 1 && control[3] == 1){
      tien(tocdo3);
    }else if(control[1] == 0 && control[2] == 1 && control[3] == 1){
      tien(tocdo2);
    }else if(control[1] == 0 && control[2] == 0 && control[3] == 1){
      tien(tocdo1);
    }else {
      tien(tocdo0);
    }
  } else if(control[0] == 1){
    if(control[1] == 1 && control[2] == 1 && control[3] == 1){
      lui(tocdo3);
    }else if(control[1] == 0 && control[2] == 1 && control[3] == 1){
      lui(tocdo2);
    }else if(control[1] == 0 && control[2] == 0 && control[3] == 1){
      lui(tocdo1);
    }else {
      lui(tocdo0);
    }
  }

  if(control[4] == 0){
    if(control[5] == 1 && control[6] == 1 && control[7] == 1){
      trai(tocdo3);
    }else if(control[5] == 0 && control[6] == 1 && control[7] == 1){
      trai(tocdo2);
    }else if(control[5] == 0 && control[6] == 0 && control[7] == 1){
      trai(tocdo1);
    }else {
      trai(tocdo0);
    }
  } else if(control[0] == 1){
    if(control[5] == 1 && control[6] == 1 && control[7] == 1){
      phai(tocdo3);
    }else if(control[5] == 0 && control[6] == 1 && control[7] == 1){
      phai(tocdo2);
    }else if(control[5] == 0 && control[6] == 0 && control[7] == 1){
      phai(tocdo1);
    }else {
      phai(tocdo0);
    }
  }


  // cat co
  if(control[8] == 1){
    cat_co();
  }else {
    dung_cat_co();
  }


  //nang ha cat
  if(control[9] == 1){
    nang_cat();
  } else if(control[10] == 1){
    ha_cat();
  } else {
    dung_ha();
  }


  //phun thuoc
  if(control[11] == 1){
    phun_thuoc();
  }else {
    dung_phun_thuoc();
  }


  //quat rai phan
  if(control[12] == 1){
    bat_quat();
  } else {
    tat_quat();
  }


  // quay camera
  if(control[13] == 1){
    xoay_sang_trai();
  } else if(control[14] == 1){
    xoay_sang_phai();
  }else{
    dung_xoay();
  }

  // nha phan
  if(control[15] == 1){
    rai_phan();
  }else {
    dung_rai();
  }
}