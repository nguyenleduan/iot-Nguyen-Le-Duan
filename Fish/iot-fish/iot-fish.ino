#include <OneButton.h>

#include <Servo.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int timecho = 1000;
unsigned long hientai = 0;
unsigned long thoigian;
// <---------Khai bao chan------>

const int SA1trig = 4;
const int SA1echo = 3;
const int SA2trig = 12;
const int SA2echo = 13;
int  relayMain = 5;
int  relayIn = 7;
int  relayOut = 6;

const int svPin = 10; // chan Servo tha thuc an
const int NUOCMIN = 20;  // khoang cách nuoc thấm nhất
const int NUOCMAX = 15;  // khoang cách nuoc thấm nhất 
// <---------khai bao bien------>
Servo sv;
LiquidCrystal_I2C lcd(0x27, 16, 2); // khai bao lcd
DS3231 rtc(SDA, SCL); // thoi gian thuc
Time time;
OneButton buttonL (9, true);
OneButton buttonM (11, true);
OneButton buttonR (2, true);
bool defaultLCD = true;
bool asdda = true;
int checkDelay = 0;

void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
  buttonR.attachClick(themnuoc); 
  buttonR.attachLongPressStart(xanuoc);
  buttonM.attachClick(thayNuoc);
  buttonL.attachClick(DayThucAn);  
  Serial.print("\n----------Start-----------------");
  lcd.init(); 
  pinMode(relayMain, OUTPUT);
  pinMode(relayIn, OUTPUT);
  pinMode(relayOut, OUTPUT);
  rtc.begin();
  lcd.backlight();
  lcd.setCursor(1, 1);
  lcd.print("HELLO");
//  buttonMEnu.attachClick(ChoAn);
//  buttonOK.attachClick(thayNuoc);
//      buttonMEnu.attachDoubleClick(ChoAn);
//  buttonOK.attachDoubleClick(themnuoc); 
  pinMode(SA1trig, OUTPUT);
  pinMode(SA1echo, INPUT);
  pinMode(SA2trig, OUTPUT);
  pinMode(SA2echo, INPUT);

    pinMode(relayIn, OUTPUT);
    pinMode(relayOut, OUTPUT);
    digitalWrite(relayIn,0); // off relayIN
    digitalWrite(relayOut,0); // on relayOut

  Serial.print("\n----------Start-----------------");
}

void asd() {
  
int pos = 0;
    sv.attach(10);
    for(pos = 0; pos < 180; pos += 1){  
        sv.write(pos);
        delay(15);
    }
    
    for(pos = 180; pos>=1; pos-=1) {                           
        sv.write(pos);
        delay(15);
    } 
}
void loop() {
  buttonL.tick();
  buttonM.tick();
  buttonR.tick();
    if (asdda) {
      sv.attach(svPin);
      sv.write(0);
      delay(1000);
      sv.detach();
      asdda = false;
    }
    time = rtc.getTime(); 
    delays();
    if (time.hour == 9 && time.min == 0 && time.sec == 0) {
      checkDelay++;
      delay(1000);
      if (true) {
        DayThucAn();
      } 
    }


    if (time.min == 30 && time.sec == 0) {
      themnuoc();
    } 
    
    if (checkDelay == 3) {
      if (time.hour == 9 && time.min == 20 && time.sec == 0) {
        xanuoc();
        checkDelay = 0;
      }   
    }
}

void delays() {
  thoigian = millis();
  if (thoigian - hientai > timecho)
  {
    hientai = millis();
    LCDDefault();
  }
}

void LCDDefault() {
  int TA = getKhoangCachSA(SA2trig, SA2echo);
  SetLCD("NC:", 0, 0, true);
  lcd.setCursor(3, 0);
  lcd.print(getKhoangCachSA(SA1trig, SA1echo));
  lcd.setCursor(7, 0);
  lcd.print(time.hour);
  SetLCD(":", 9, 0, false);
  lcd.setCursor(10, 0);
  lcd.print(time.min);
  SetLCD(":", 12, 0, false);
  lcd.setCursor(13, 0);
  lcd.print(time.sec);
  // -------1-------
  SetLCD("TA:", 0, 1, false);
  lcd.setCursor(3, 1);
  lcd.print(TA);
  SetLCD("NLD TECH", 5, 1, false);
  lcd.setCursor(14, 1);
  lcd.print(checkDelay);
  SetLCD("D", 15, 1, false);
}

void SetLCD(String mess, int hang, int cot, bool clear) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(hang, cot);
  lcd.print(mess);
}
 
void DayThucAn() {
  sv.attach(svPin);
  SetLCD("Dang cho an ....", 0, 0, true);
  sv.write(0);
  delay(1000);
  sv.write(30);
  delay(1000);
  delay(1000);
  sv.write(90);
  delay(1000);
  sv.write(150);
  delay(1000);
  sv.write(90);
  delay(1000);
  sv.write(0);
  delay(1000);
  sv.detach();
  defaultLCD = true;
}
int getKhoangCachSA(int trig, int echo) {
  //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig, 0); //Tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig, 0);
  return int ( pulseIn (echo, HIGH) / 2 / 29.412); // trả về khoảng cách CM
}
void themnuoc() {  
  digitalWrite(relayMain, HIGH);
  delay(1000);
  while (getKhoangCachSA(SA1trig, SA1echo) >= NUOCMAX ) { 
  digitalWrite(relayIn, HIGH); 
  Serial.print("\n----------In-----------------");
    delay(2000);
  }  
  digitalWrite(relayIn, LOW); 
  delay(500); 
  digitalWrite(relayMain, LOW);
  delay(500); 
}
void xanuoc() { 
  digitalWrite(relayMain, HIGH); 
  delay(1000);
  while (getKhoangCachSA(SA1trig, SA1echo) <= NUOCMIN ) { 
  digitalWrite(relayOut, HIGH);  
  Serial.print("\n----------Out-----------------");
    delay(2000);
  } 
  digitalWrite(relayOut, LOW); 
  delay(500); 
  digitalWrite(relayMain, LOW);
  delay(500); 
}
void thayNuoc() {
  digitalWrite(relayMain, HIGH); 
  delay(1000);
  while (getKhoangCachSA(SA1trig, SA1echo) <= NUOCMIN ) { 
  digitalWrite(relayOut, HIGH);  
  Serial.print("\n----------Out-----------------");
    delay(2000);
  } 
  digitalWrite(relayOut, LOW); 
  delay(1000);
  while (getKhoangCachSA(SA1trig, SA1echo) >= NUOCMAX ) { 
  digitalWrite(relayIn, HIGH); 
  Serial.print("\n----------In-----------------");
    delay(2000);
  }  
  delay(1000);
  digitalWrite(relayIn, LOW);
  digitalWrite(relayMain, LOW);
  
  Serial.print("\n---------end----------------");
}
