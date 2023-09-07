/*
0:1 bit dieu khien tien (0) va lui (1)
1:2 bit dieu khien truc x
3:1 bit dieu khien trai (0) va phai (1)
5:2 bit dieu khien truc y 

6:1 bit dieu khien cat
7:1 bit dieu khien gian cat nang
8:1 bit dieu khien gian cat ha

9:1 bit dieu khien phun
10:1 bit bat / tat quat phan
11:1 bit dong /  nha phan

12:1 bit quay trai step
13:1 bit quay phai step
14:1 bit chinh cam nang len
15:1 bit chinh cam huong xuong

0 12 3 45 6 7 8 9 10  11  12  13  14  15
0 00 0 00 0 0 0 0 0   0   0   0   0   0

B1-D8   -> ha cat
B2-D9   -> nang cat
B3-D2   -> nha phan
B4-D3
T1-D7   -> cat co
T2-D4   -> quat phan
POT1-A7 -> phun thuoc
POT2-A6
CE-D5   -> nrf
CSN-D6  -> nrf
XL-A0   -> tien lui
YL-A1   -> trai phai
YR-A2   -> cam trai phai
XR-A3   -> cam nang ha
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(5, 6);                 // CE, CSN
const byte address[6] = "00001";  //address through which two modules communicate.
byte control[32] = { 0 };         // lenh dieu khien hoat dong 1
#define quat_phan 4 
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
  pinMode(quat_phan, INPUT_PULLUP);
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
  // doc du lieu dieu khien tu joytick
  int LX_axis = analogRead(A0);
  int LY_axis = analogRead(A1);
  int RY_axis = analogRead(A2);
  int RX_axis = analogRead(A3);

  // chuyen doi thang do ve 3 muc toc do
  int speedX = map(LX_axis, 0, 1024, -3, 3);
  int speedY = map(LY_axis, 0, 1024, -3, 3);

  // nhap bit vao lenh gui
  if (speedX > 0) {
    control[0] = 0;  // xac dinh tien ve phia truoc
    switch (speedX) {
      case 1:  // tien voi toc do 1
        control[1] = 0;
        control[2] = 1;
        break;
      case 2:  // tien voi toc do 2
        control[1] = 1;
        control[2] = 0;
        break;
      case 3:  // tien voi toc do 3
        control[1] = 1;
        control[2] = 1;
        break;
      default:  // dung lai
        control[1] = 0;
        control[2] = 0;
        break;
    }
  } else if (speedX < 0) {
    control[0] = 1;  // xac dinh lui ve sau
    switch (speedX) {
      case -1:  // lui ve sau voi toc do 1
        control[1] = 0;
        control[2] = 1;
        break;
      case -2:  // lui ve sau voi toc do 2
        control[1] = 1;
        control[2] = 0;
        break;
      case -3:  // lui ve sau voi toc do 3
        control[1] = 1;
        control[2] = 1;
        break;
      default:  // dung lai
        control[1] = 0;
        control[2] = 0;
        break;
    }
  } else {  // dung di chuyen
    control[0] = 0;
    control[1] = 0;
    control[2] = 0;
  }


  if (speedY > 0) {
    control[3] = 0;  // di chuyen sang trai
    switch (speedY) {
      case 1:  // di chuyen sang trai voi toc do 1
        control[4] = 0;
        control[5] = 1;
        break;
      case 2:  //di chuyen sang trai voi toc do 2
        control[4] = 1;
        control[5] = 0;
        break;
      case 3:  // di chuyen sang trai voi toc do 3
        control[4] = 1;
        control[5] = 1;
        break;
      default:  // dung lai
        control[4] = 0;
        control[5] = 0;
        break;
    }
  } else if (speedY < 0) {
    control[3] = 1;  // di chuyen sang phai
    switch (speedY) {
      case -1:  // di chuyen sang phai voi toc do 1
        control[4] = 0;
        control[5] = 1;
        break;
      case -2:  // di chuyen sang phai voi toc do 2
        control[4] = 1;
        control[5] = 0;
        break;
      case -3:  // di chuyen sang phai voi toc do 3
        control[4] = 1;
        control[5] = 1;
        break;
      default:  // dung lai
        control[4] = 0;
        control[5] = 0;
        break;
    }
  } else {  // dung di chuyen
    control[3] = 0;
    control[4] = 0;
    control[5] = 0;
  }
  // ket thuc nhap lenh di chuyen



  // dieu khien cam
  if(RX_axis > 712){
    control[14] = 1;
    control[15] = 0;
  }else if(RX_axis < 312){
    control[14] = 0;
    control[15] = 1;
  }else {
    control[14] = 0;
    control[15] = 0;
  }

  if (RY_axis < 312) {  // xoay step sang phai
    control[12] = 0;
    control[13] = 1;
  } else if (RY_axis > 712) {  // xoay step sang trai
    control[12] = 1;
    control[13] = 0;
  } else {  // cho servo dung im
    control[12] = 0;
    control[13] = 0;
  }


  // doc tin hieu tu nut nhan
  int signal_quat = digitalRead(quat_phan);
  int signal_phun = digitalRead(phun);
  int signal_cat = digitalRead(cat);
  int signal_ha_cat = digitalRead(ha_cat);
  int signal_nang_cat = digitalRead(nang_cat);
  int signal_nha_phan = digitalRead(nha_phan);

  //nhap bit dieu khien
  if(signal_cat == 0){
    control[6] = 1;
  } else {
    control[6] = 0;
  }

  if(signal_nang_cat == 0){
    control[7] = 1;
    control[8] = 0;
  }else if(signal_ha_cat == 0){
    control[7] = 0;
    control[8] = 1;
  } else {
    control[7] = 0;
    control[8] = 0;
  }

  if(signal_phun == 0){
    control[9] = 1;
  } else {
    control[9] = 0;
  }

  if(signal_quat == 0){
    control[10] = 1;
  }else {
    control[10] = 0;
  }

  if(signal_nha_phan == 0){
    control[11] = 1;
  }else {
    control[11] = 0;
  }

  
  send_data(control);
}