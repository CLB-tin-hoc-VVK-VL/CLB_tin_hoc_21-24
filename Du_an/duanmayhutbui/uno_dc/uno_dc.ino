//----------l298

#define pwmb 5
#define pwma 6
#define in3 4
#define in2 8
#define in1 7
#define in4 9

//-----------he thong cam bien

#define tinHieuTrai A0
#define tinHieuPhai A5
#define tinHieuGiua1 A2
#define tinHieuGiua2 A3
#define tinHieuTrai2 A1
#define tinHieuPhai2 A4

//------------doc xung dong co

#define rupt1 0 // digital 2
#define rupt2 1 // digital 3
#define B1 10
#define B2 11

//-------------khai bao bien
long xungdctrai = 0, xungdcphai = 0, bandautrai, bandauphai;

String data = "";

//--------------cai dat

void setup() {
  Serial.begin(9600);
  for (int i = 2; i < 14; i ++) {
    if (i < 4) pinMode(i, INPUT_PULLUP);
    else if ( 4 <= i && i <= 9) pinMode(i, OUTPUT);
    else if ( 10 <= i && i <= 13) pinMode(i, INPUT);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  attachInterrupt(rupt1, nhanxung1, FALLING);
  attachInterrupt(rupt2, nhanxung2, FALLING);
}


/* doc xung tu dong co
  ----------------------
*/
void nhanxung1() {
  if (digitalRead(B1) == 1) {
    xungdctrai ++;
  } else {
    xungdctrai --;
  }
}
void nhanxung2() {
  if (digitalRead(B2) == LOW) {
    xungdcphai ++;
  } else {
    xungdcphai --;
  }
}


/* nhom lenh dieu khien dong co
  -------------------------------
*/
void traitien() {
  analogWrite(pwmb, 255);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void phaitien() {
  analogWrite(pwma, 255);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
}

void trailui() {
  analogWrite(pwmb, 255);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void phailui() {
  analogWrite(pwma, 255);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
}

void dung() {
  analogWrite(pwma, 0);
  analogWrite(pwmb, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  delay(100);
}


/* nhom lenh xu ly tin hieu
  ---------------------------
*/
void vatcanbentrai() {
  if (digitalRead(tinHieuTrai) == 0 || digitalRead(tinHieuTrai2) == 0) {
    trailui();
    phailui();

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.print("trai-lui   ");
    //      Serial.println(abs(xungdctrai - bandautrai));
    //      if (abs(xungdctrai - bandautrai) >= 2700)break;
    //    }
    delay(1000);

    traitien();
    phailui();

    xungdctrai = 0;
    xungdcphai = 0;

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.println("trai-re");
    //      if (abs(xungdctrai - bandautrai) >= 1600 && abs(xungdcphai - bandauphai) >= 1600) break;
    //    }
    delay(1500);

    traitien();
    phaitien();
  }
}

void vatcanbenphai() {
  if (digitalRead(tinHieuPhai) == 0 || digitalRead(tinHieuPhai2) == 0 ) {
    trailui();
    phailui();

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.println("phai-lui");
    //      if (abs(xungdctrai - bandautrai) >= 2700)break;
    //    }
    delay(1000);

    trailui();
    phaitien();

    xungdctrai = 0;
    xungdcphai = 0;

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.println("phai-re");
    //      if (abs(xungdctrai - bandautrai) >= 1600 && abs(xungdcphai - bandauphai) >= 1600) break;
    //    }
    delay(1500);

    traitien();
    phaitien();
  }
}

void vatcangiua() {
  bool giua1 = digitalRead(tinHieuGiua1), giua2 = digitalRead(tinHieuGiua2);
  if (giua2 == 0 || giua1 == 0) {
    trailui();
    phailui();

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.println("lui");
    //      if (abs(xungdctrai - bandautrai) >= 2700)break;
    //    }
    delay(1000);

    if (giua1 == 0) {
      traitien();
      phailui();
    }
    else if (giua2 == 0) {
      phaitien();
      trailui();
    }

    xungdctrai = 0;
    xungdcphai = 0;

    bandautrai = xungdctrai;
    bandauphai = xungdcphai;

    //    while (true) {
    //      Serial.println("giua-re");
    //      if (abs(xungdctrai - bandautrai) >= 1600 && abs(xungdcphai - bandauphai) >= 1600) break;
    //    }
    delay(1500);
    traitien();
    phaitien();
  }
}

/* vong lap
  -----------------
*/
void loop() {
  phaitien();
  traitien();
  vatcanbentrai();
  vatcanbenphai();
  vatcangiua();
  //Serial.print("xung trai: ");
  //Serial.println(xungdctrai);
  //Serial.print("   xung phai: ");
  //Serial.println(xungdcphai);

}
