/*
tao lenh dieu khien hoat dong 16 bit voi cac bit dieu khien mot chuc nang

1:1 bit dieu khien tien (0) va lui (1)
2:3 bit dieu khien truc x
4:1 bit dieu khien trai (0) va phai (1)
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

B2 - D9 dieu khien nang gian cat
B1 - D8 dieu khien ha gian cat
T1 - D7 dieu khien bat / tat cat
POT1 - A7 dieu khien bat / tat phun 
T2 - D4 dieu khien bat / tat quat rai phan
B3 - D2 dieu khien bat / tat nha phan
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 8);                 // CE, CSN
const byte address[6] = "00001";  //address through which two modules communicate.
byte control[32] = { 0 };         // lenh dieu khien hoat dong 1
#define phan 4 
#define nha_phan 2
#define phun A7
#define cat 7 
#define ha_cat 8 
#define nang_cat 9


  void
  setup() {
  //----------set up for nrf module
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  //----------end set up

  //----------set up chan doc du lieu
  pinMode(phan, INPUT_PULLUP);
  pinMode(nha_phan, INPUT_PULLUP);
  pinMode(phun, INPUT_PULLUP);
  pinMode(cat, INPUT_PULLUP);
  pinMode(ha_cat, INPUT_PULLUP);
  pinMode(nang_cat, INPUT_PULLUP);
}


// ham gui du lieu ve mach thu
void send_data(char content[]) {
  radio.write(&content, sizeof(content));
}


void loop() {
  // doc du lieu dieu khien di chuyen tu joytick
  int X_axis = analogRead(A0);
  int Y_axis = analogRead(A1);

  // chuyen doi thang do ve 3 muc toc do
  int speedX = map(X_axis, 0, 1024, -3, 3);
  int speedY = map(Y_axis, 0, 1024, -3, 3);

  // nhap bit vao lenh gui
  if (speedX > 0) {
    control[0] = 0;  // xac dinh tien ve phia truoc
    switch (speedX) {
      case 1:  // tien voi toc do 1
        control[1] = 0;
        control[2] = 0;
        control[3] = 1;
        break;
      case 2:  // tien voi toc do 2
        control[1] = 0;
        control[2] = 1;
        control[3] = 1;
        break;
      case 3:  // tien voi toc do 3
        control[1] = 1;
        control[2] = 1;
        control[3] = 1;
        break;
      default:  // dung lai
        control[1] = 0;
        control[2] = 0;
        control[3] = 0;
        break;
    }
  } else if (speedX < 0) {
    control[0] = 1;  // xac dinh lui ve sau
    switch (speedX) {
      case -1:  // lui ve sau voi toc do 1
        control[1] = 0;
        control[2] = 0;
        control[3] = 1;
        break;
      case -2:  // lui ve sau voi toc do 2
        control[1] = 0;
        control[2] = 1;
        control[3] = 1;
        break;
      case -3:  // lui ve sau voi toc do 3
        control[1] = 1;
        control[2] = 1;
        control[3] = 1;
        break;
      default:  // dung lai
        control[1] = 0;
        control[2] = 0;
        control[3] = 0;
        break;
    }
  } else {  // dung di chuyen
    control[0] = 0;
    control[1] = 0;
    control[2] = 0;
    control[3] = 0;
  }


  if (speedY > 0) {
    control[4] = 0;  // di chuyen sang trai
    switch (speedY) {
      case 1:  // di chuyen sang trai voi toc do 1
        control[5] = 0;
        control[6] = 0;
        control[7] = 1;
        break;
      case 2:  //di chuyen sang trai voi toc do 2
        control[5] = 0;
        control[6] = 1;
        control[7] = 1;
        break;
      case 3:  // di chuyen sang trai voi toc do 3
        control[5] = 1;
        control[6] = 1;
        control[7] = 1;
        break;
      default:  // dung lai
        control[5] = 0;
        control[6] = 0;
        control[7] = 0;
        break;
    }
  } else if (speedY < 0) {
    control[4] = 1;  // di chuyen sang phai
    switch (speedY) {
      case -1:  // di chuyen sang phai voi toc do 1
        control[5] = 0;
        control[6] = 0;
        control[7] = 1;
        break;
      case -2:  // di chuyen sang phai voi toc do 2
        control[5] = 0;
        control[6] = 1;
        control[7] = 1;
        break;
      case -3:  // di chuyen sang phai voi toc do 3
        control[5] = 1;
        control[6] = 1;
        control[7] = 1;
        break;
      default:  // dung lai
        control[5] = 0;
        control[6] = 0;
        control[7] = 0;
        break;
    }
  } else {  // dung di chuyen
    control[4] = 0;
    control[5] = 0;
    control[6] = 0;
    control[7] = 0;
  }
  // ket thuc nhap lenh di chuyen




  // doc du lieu dieu khien servo
  int Y_servo = analogRead(A3);

  if (Y_servo > 712) {  // xoay servo sang phai
    control[13] = 0;
    control[14] = 1;
  } else if (Y_servo < 312) {  // xoay servo sang trai
    control[13] = 1;
    control[14] = 0;
  } else {  // cho servo dung im
    control[13] = 0;
    control[14] = 0;
  }


  // doc tin hieu tu nut nhan
  int signal_phan = digitalRead(phan);
  int signal_phun = digitalRead(phun);
  int signal_cat = digitalRead(cat);
  int signal_ha_cat = digitalRead(ha_cat);
  int signal_nang_cat = digitalRead(nang_cat);
  int signal_nha_phan = digitalRead(nha_phan);

  //nhap bit dieu khien
  if(signal_cat == 0){
    control[8] = 1;
  } else {
    control[8] = 0;
  }

  if(signal_nang_cat == 0){
    control[9] = 1;
  }else if(signal_ha_cat == 0){
    control[10] = 1;
  } else {
    control[9] = 0;
    control[10] = 0;
  }

  if(signal_phun == 0){
    control[11] = 1;
  } else {
    control[11] = 0;
  }

  if(signal_phan == 0){
    control[12] = 1;
  }else {
    control[12] = 0;
  }

  if(signal_nha_phan == 0){
    control[15] = 1;
  }else {
    control[15] = 0;
  }

  
  send_data(control);
}