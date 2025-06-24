//const int LED = 13; //Sử dụng chân 13 điều khiển đèn LED
String data = "";   //Khai báo biến data lưu lệnh mà master gửi đến

void setup()
{
  //  pinMode(LED, OUTPUT); // Khai báo sử dụng pin số 13 làm OUTPUT
  //  digitalWrite(LED, LOW); // Ban đầu cho đèn LED tắt
  Serial.begin(9600); // Khai báo sử dụng Serial với tốc độ baud = 9600
}
void loop() {
  /*lay du lieu duoc gui ve

  */
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      Serial.println(data);
      nhanlenh(data);
      data = "";
    } else {
      data = data + c;
    }
  }
}
bool trai = 0;
bool phai = 0;
/*nhan lenh, xu ly lenh

*/
void nhanlenh(String lenh) {
  if ( lenh == "[CONTROL]-tinhieu-trai-1") {
    trai = 1;
  }
  else if ( lenh == "[CONTROL]-tinhieu-phai-0") {
    phai = 0;
  }
  else if ( lenh == "[CONTROL]-tinhieu-phai-1") {
    phai = 1;
  }
  else if ( lenh == "[CONTROL]-tinhieu-trai-0") {
    trai = 0;
  }
}
