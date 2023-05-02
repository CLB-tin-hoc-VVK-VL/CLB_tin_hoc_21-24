#include <LiquidCrystal_I2C.h>

/*khoi tao lcd, doc ban phim va bien toan cuc
 * 
 * 
 */
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define scl16 D3
#define sdo16 D4
#define bientro A0

int oldnum = 0, so = 0, olddnum = 0, chon = 0, oldchoo = 0;
const byte kituchuan = 32;

/*cai dat ban dau
 * 
 * 
 */
void setup() {
  //cai dat cho phim 16
  pinMode(scl16, OUTPUT);
  pinMode(sdo16, INPUT);
  
  // cai dat cho lcd
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 1); // cot, dong
  lcd.print(" SMART VACCUM HELLO ");
  lcd.setCursor(0, 2);
  lcd.print("    start engine");
  delay(1500);
  lcd.clear();

  //tao ki tu
  byte nga[8] = {
    B00000,
    B00000,
    B01000,
    B10101,
    B00010,
    B00000,
    B00000,
    B00000,
  };

  byte xtrai[8] = {
    B00000,
    B10000,
    B01000,
    B00100,
    B00010,
    B00001,
    B00000,
    B00000,
  };

  byte xoa[8] = {
    B00000,
    B00010,
    B00100,
    B01000,
    B11111,
    B01000,
    B00100,
    B00010,
  };

  byte cach[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B10001,
    B11111,
    B00000,
  };

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
  
  lcd.createChar(0,nga);
  lcd.createChar(1, xtrai);
  lcd.createChar(2, xoa);
  lcd.createChar(3, cach);
  lcd.createChar(4, trong);

  Serial.begin(115200);
 }

/* vong lap
 *  
 *  
 */
void loop() {
  so = getkey();
  chon = choo();

  if (oldnum != so && so != 0){
    xoahang(3);
    lcd.setCursor(18, 3);
    lcd.print(oldnum);
    hienthihuongdan(oldnum);
    if (oldnum != 0) olddnum = oldnum;
    oldnum = so;
  }

  Serial.print(so);
  
  Serial.print(oldnum);
  Serial.print(" ,");
  Serial.println(olddnum);
  
  if (oldchoo != chon && oldnum != 15&& oldnum != 16){
    xoao(0, 0);
    lcd.setCursor(0, 0);
    lcou(xlchon(chon, oldnum));
    oldchoo = chon;
  }
}

/*doc phim cam ung
 * 
 * 
 */
byte getkey(void)
{
  byte cnt;
  byte num = 0;
  for(cnt = 1; cnt < 17; cnt++)
  {
    digitalWrite(scl16, LOW); 
    if (digitalRead(sdo16) == 0)
      num = cnt; 
    digitalWrite(scl16, HIGH);
  }  
  return num; 
}

/*lua chon
 * 
 * 
 */
byte choo(void){
  int value;
  value = map(analogRead(bientro), 1, 1024, 0, 6);
  return value;
}

/*show phim
 * 
 * 
 */
void hienthihuongdan(int num){
  int pos = 0;
  if (num == 15){
    lcd.setCursor(0, 3);
    lcd.write(byte(2));  
  }else if (num == 16){
    lcd.setCursor(0, 3);
    lcd.write(byte(3));
  }else {
    for(int i = kituchuan+(num-1)*7; i < kituchuan+num*7 && num > 0; i ++){
      lcd.setCursor(pos, 3);
      char kt = char(i);
      lcou(kt);
      pos += 2;
    }
  }
}

/*xu ly lua chon
 * 
 * 
 */
char xlchon(int bt, int num16){
  char kitu;
  kitu = bt + kituchuan+(num16-1)*7;
  return kitu;
}

/*xuat ra lcd
 * 
 * 
 */
void lcou(char sys){
  if(sys == '~'){
    lcd.write(byte(0));
  }else if(sys == '\\'){
    lcd.write(byte(1));
  }else if(sys == ' '){
    lcd.write(byte(3));
  }else if(int(sys) != 127){
    lcd.print(sys);
  }
 }

/*xoa hang
 * 
 * 
 */
void xoahang(int hang){
  for(int i = 0; i < 20; i++){
    lcd.setCursor(i, hang);
    lcd.write(byte(4));
  }
}

/*xoa o
 * 
 * 
 */
void xoao(int cot, int hang){
  lcd.setCursor(cot, hang);
  lcd.write(byte(4));
}
