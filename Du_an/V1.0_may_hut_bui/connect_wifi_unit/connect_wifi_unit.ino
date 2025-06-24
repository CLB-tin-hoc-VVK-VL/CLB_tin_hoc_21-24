#define BLYNK_PRINT Serial      // in tren serial
#define resetPin D0             // reset wifi pin

#include <WiFiManager.h>        // thu vien quan ly wifi
#include <ESP8266WiFi.h>        // thu vien wifi
#include <BlynkSimpleEsp8266.h> // thu vien lien ket Blynk
#include <LiquidCrystal_I2C.h>  // thu vien LCD

LiquidCrystal_I2C lcd(0x27, 20, 4); // dinh nghia cld
// scl -> D1 : sda -> D2

WiFiManager wm; // dinh nghia quan ly wifi

unsigned long status_ = millis();   // thoi gian de reset
unsigned long checkEror = millis(); // kiem tra xay ra loi

char auth[] = "hHcEtg5aFhtb2bmTh5yaqF5EKDv7_27u";  // ma lien ket voi Blynk. Thay doi de phu hop tuy thuoc du an

void setup() {
    /*
     * cac thao tac cai dat LCD
     */
    lcd.init();
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 1);
    lcd.print(" SMART VACCUM HELLO ");
    lcd.setCursor(0, 2);
    lcd.print("    start engine");
    delay(1500);
    lcd.clear();
    /*
     * 
     */

     // ki tu trong
     byte trong[8] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
    };
    lcd.createChar(4, trong);
  
    WiFi.mode(WIFI_STA); // che do ket noi
    Serial.begin(9600); // khoi tao serial
    
    pinMode(resetPin, INPUT_PULLUP); // khoi tao chan doc tin hieu
    pinMode(D4, OUTPUT);
    setupWifi(); // ham cai dat ket noi wifi    
}

//---------------------------------------------------------------------------------------

/*  
 * set up and connect wifi
 */
 void setupWifi(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connect to setup:");
  lcd.setCursor(0, 2);
  lcd.print("ssid: VACUUM-01");
  lcd.setCursor(0, 3);
  lcd.print("pass: damhb-01");
  delay(2500);
  
  
  xoahang(0);
  lcd.setCursor(0, 0);
  lcd.print("Connecting . . .");
  
  bool res; // bien luu trang thai ket noi
  res = wm.autoConnect("VACUUM-01","damhb-01"); // SSID va PASS khi o che do accesspoint
  checkEror = millis();

/*
 * kiem tra tinh trang ket noi 
 */
  if (res){
    //ket noi thanh cong se lien ket voi Blynk

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wifi connected...");
    String wmssid = wm.getWiFiSSID();
    String wmpass = wm.getWiFiPass();
    char ssid[wmssid.length()+1];
    char pass[wmpass.length()+1];
    
    wmssid.toCharArray(ssid, wmssid.length()+1);
    wmpass.toCharArray(pass, wmpass.length()+1);
    
//    Blynk.begin(auth, ssid, pass);
    lcd.setCursor(0, 1);
    lcd.print("Bynk conneccted ...");
    delay(2500);
    lcd.clear();
  }
}

/*
 * ham dat lai wifi
 */
void resetWifi(void){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reset Wifi");
  wm.resetSettings(); 
  delay(2500);
  setupWifi();
}

/* 
 * ham xoa hang 
 */
void xoahang(int hang){
  for(int i = 0; i < 20; i++){
    lcd.setCursor(i, hang);
    lcd.write(byte(4));
  }
}

/*
 * ham xoa o 
 */
void xoao(int cot, int hang){
  lcd.setCursor(cot, hang);
  lcd.write(byte(4));
}

//------------------------ vong lap -----------------------------------------------------
void loop() {
  if(digitalRead(resetPin) == 0 and (millis() - status_) > 5000){
    resetWifi();
    status_ = millis();
  }
  Blynk.run();
}
