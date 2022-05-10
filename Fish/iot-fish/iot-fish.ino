#include <DS3231.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// <---------Khai bao chan------>
const int minuteOnOff =2;
const int SA1trig = 11; // Chan 8 trig cua SA1
const int SA1echo = 11; // Chan 7 echo cua SA1
const int SA2trig= 7; // Chan 13 trig cua SA1
const int SA2echo= 8;  // Chan 12 echo cua SA2

const int relayIn= 3;  // Chan relayIn 3
const int relayOut= 2;  // Chan relayOut 2 

const int valueMaxBox= 5;  // Khoang cach khi nuoc day box CM
const int valueMinBox= 20;  // Khoang cach khi nuoc day box CM
// <--------------->
LiquidCrystal_I2C lcd(0x27,16,2);  // khai bao lcd
DS3231 rtc(SDA,SCL); // thoi gian thuc 
Time time;    
void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
  lcd.init();
  lcd.backlight(); 
  
  // pinMode(SA1trig, OUTPUT); //Chân trig xuất tín hiệu
  // pinMode(SA1echo, INPUT); 
  pinMode(SA2trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(SA2echo, INPUT);    
  pinMode(relayIn, OUTPUT);     
  pinMode(relayOut, OUTPUT);   
  digitalWrite(relayIn,0); // off relayIN 
  digitalWrite(relayOut,0); // on relayOut  
}

void loop() {    
// get khoang cach SA1 
// int kc  = getKhoangCachSA(SA1trig,SA1echo);
// get khoang cach SA2
// int kc  = getKhoangCachSA(SA2trig,SA2echo);
// ------------------------------------------------------------


  // Serial.print("Khoảng cách: ");
  // Serial.print(khoangcach);
  // Serial.println("cm");
thayNuoc();

  
      lcd.setCursor(0, 0); // set vi tri show
      lcd.print(" DONE :");  // noi dung    
      lcd.setCursor(5, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA2trig,SA2echo));  // noi dung    
      delay(5000); 
      lcd.clear(); 


}
void setupSA(){
  pinMode(SA1trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(SA1echo, INPUT); 
  pinMode(SA2trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(SA2echo, INPUT);    
  pinMode(relayIn, OUTPUT);     
  pinMode(relayOut, OUTPUT);   
}

int getKhoangCachSA(int trig,int echo){  
   //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0); 
  return int ( pulseIn (echo, HIGH) / 2 / 29.412); // trả về khoảng cách CM
} 
void thayNuoc(){
  if(getKhoangCachSA(SA2trig,SA2echo)<10){ /// muc nuoc trong box < 50%
    digitalWrite(relayIn,0); // off relayIN 
    digitalWrite(relayOut,1); // on relayOut  
    while (getKhoangCachSA(SA2trig,SA2echo) <= valueMinBox ){ //5++  10 
      lcd.setCursor(0, 0); // set vi tri show
      lcd.print("Xa nuoc :");  // noi dung    
      lcd.setCursor(5, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA2trig,SA2echo));  // noi dung    
      delay(500); 
      lcd.clear(); 
    } 
    themNuoc(); // them nuoc vao box
  }else{ 
    themNuoc(); // them nuoc vao box
  } 
  themNuoc(); /// check nuoc lan cuoi
}
void themNuoc(){
  if(getKhoangCachSA(SA2trig,SA2echo)>= 20){ /// muc nuoc trong box < 80% 
    digitalWrite(relayOut,0); // off relayOut  
    digitalWrite(relayIn,1); // on relayIN 
    while (getKhoangCachSA(SA2trig,SA2echo) >= valueMaxBox ){ //12--  10 
      lcd.setCursor(0, 0); // set vi tri show
      lcd.print("them nuoc :");  // noi dung    
      lcd.setCursor(5, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA2trig,SA2echo));  // noi dung    
      delay(500); 
      lcd.clear(); 
    } 
    digitalWrite(relayIn,0); // off relayIN 
  } 
}
