#include <OneButton.h>

#include <Servo.h>  
#include <DS3231.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 


const int SA1trig = 13;  
const int SA1echo = 12;  
//const int SA2trig= 0; // Chan 13 trig cua SA1
//const int SA2echo= 3;  // Chan 12 echo cua SA2 
//const int svPULLPin = 10; // chan Servo tha thuc an
//const int svPUSHPin =9; // chan Servo day thuc an 
const int ButtonMEnu = 2;  // Chan button menu 
const int ButtonControll = 8;  // Chan button controll 
#define lat 7
#define clo 6
#define data 5

// <---------khai bao bien------> 
LiquidCrystal_I2C lcd(0x27,16,2);  // khai bao lcd
OneButton buttonMEnu (ButtonMEnu,true);
OneButton buttonOK (ButtonControll,true); 
int menu = 0;
int menuChill = 0;
int btMenu = 0; 
int valueMenu = 0; 
int ckickOK = 0; 

void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
 Serial.print("\n----------Start-----------------"); 
 
  lcd.init(); 
  pinMode(lat, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clo, OUTPUT);


//  rtc.begin();
  lcd.setCursor(1, 1);
  lcd.print("HELLO");
  lcd.backlight(); 

  buttonMEnu.attachClick(funtionMenu);
  buttonOK.attachClick(funtionMenuChill);
  
   pinMode(SA1trig, OUTPUT); //Chân trig xuất tín hiệu
   pinMode(SA1echo, INPUT); 

}

void loop() {
 
  buttonMEnu.tick(); //Kiểm tra trạng thái nút nhấn 
  buttonOK.tick(); //Kiểm tra trạng thái nút nhấn 

}

void funtionMenu(){ 
  lcd.clear();
 Serial.print("\n");
 Serial.print(getKhoangCachSA(SA1trig,SA1echo)); 
 ckickOK=1;
 if(btMenu == 1){
    switch (menu)
       {

            /*
             * 
               -1: tro ve menu
               1: thay nuoc
               2: them nuoc
               3: xa nuoc
               4: xa nuoc 30s // tuy chỉnh 
               5: cho an
               6: day thuc an 5s 
               7: day thuc an 20s
               8: day thuc an 1p
               9: tha thuc an
               
             * 
             */ 
           ////////// NUOC //////////
           case 1:  
           { 
             valueMenu = 1;
             SetLCD("> 1. Thay nuoc",0,0,true); 
             SetLCD("  2. Them nuoc",0,1,false); 
             menu = 4; 
                break;
           } 
           case 4: 
           { 
             valueMenu = 2;
             SetLCD("> 2. Them nuoc",0,0,true); 
             SetLCD("  3. Tro ve",0,1,false); 
             menu = 5; 
                break;
           }
           case 5:  
           { 
             valueMenu = 3;
             SetLCD("> 3. Xa nuoc",0,0,true); 
             SetLCD("  4. Xa nuoc 10s",0,1,false);  
             menu = 6; 
                break;
           } 
           case 6:  
           { 
             valueMenu = 4;
             SetLCD("> 4. Xa nuoc 10s",0,0,true); 
             SetLCD("  5. Tro ve",0,1,false);  
             menu = 7; 
                break;
           }
           case 7:  
           { 
             valueMenu = -1;
             SetLCD("> 5. Tro ve",1,0,true); 
             menu = 1;  
                break;
           } 
           ////////// Thuc An  ////////// 
           case 2:  
           { 
             valueMenu = 5;
             SetLCD("> 1. Cho an",0,0,true); 
             SetLCD("  2. Day TA 5L",0,1,false); 
             menu = 8; 
                break;
           } 
           case 8: 
           { 
             valueMenu = 6;
             SetLCD("> 2. Day TA 5L",0,0,true); 
             SetLCD("  3. Day TA 10L",0,1,false); 
             menu = 9; 
                break;
           }
           case 9:  
           { 
             valueMenu = 7;
             SetLCD("> 4. Day TA 20L",0,0,true); 
             SetLCD("  5. Tha thuc an",0,1,false); 
             menu = 10; 
                break;
           }
           case 10:  
           { 
             valueMenu = 8;
             SetLCD("> 5. Tha thuc an",0,0,true); 
             SetLCD("  6. Tro ve",0,1,false); 
             menu = 11; 
                break;
           }
           case 11:  
           { 
//             valueMenu = 9;
             SetLCD("> 6. Tro ve",0,0,true); 
             menu = 2;  
              valueMenu=-1;
                break;
           }
       }
   }else{ 
      switch (menu)
        {
            case 0:
            { 
              SetLCD("--MENU---",3,0,true); 
              SetLCD("> 1. Nuoc",0,1,false); 
              menu = 1; 
                break;
            }
            case 1:
            {
                // NUOC 
              SetLCD("> 1. Nuoc",0,0,true); 
              SetLCD("  2. Thuc an ",0,1,false); 
              menu = 2; 
                break;
            } 
            case 2:
            {
                // Thuc an
              SetLCD("> 2. Thuc an",0,0,true); 
              SetLCD("  3. Tro ve",0,1,false); 
              menu = 3; 
                break;
            }
            case 3:
            {
                // tro ve
              SetLCD("> 3. Tro ve",0,0,true); 
              SetLCD("MENU",6,1,false); 
              menu = 0;
              btMenu = 0;
              valueMenu=-1;
                break; 
            } 
        }
       }
} 
 void funtionMenuChill(){  
  if(ckickOK==1){
    
      if(menu == 0){
        btMenu = 0 ;
      } 
      if(btMenu != 1){
        btMenu =1 ;
      }else{
        switch (valueMenu)
            {
                case -1:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: -1"); 
                    lcd.clear(); ckickOK==0;
                    break;
                } 
                case 1:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 1"); 
                     funtionMenu();
                    break;
                } 
                case 2:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 2"); 
                     funtionMenu();
                    break;
                } 
                case 3:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 3"); 
                     funtionMenu();
                    break;
                } 
                case 4:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 4"); 
                     funtionMenu();
                    break;
                } 
                case 5:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 5"); 
                     funtionMenu();
                    break;
                } 
                case 6:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 6"); 
                     funtionMenu();
                    break;
                } 
                case 7:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 7"); 
                     funtionMenu();
                    break;
                } 
                case 8:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 8"); 
                     funtionMenu();
                    break;
                } 
                case 9:
                {  menu = 0; 
                  btMenu = 0;
                    Serial.print("\nĐếm xxx: 9"); 
                     funtionMenu();
                    break;
                } 
            }
                 
      }
  }
 }


void SetLCD(String mess, int hang, int cot, bool clear){
  if(clear){
    lcd.clear(); 
  } 
   lcd.setCursor(hang, cot);
   lcd.print(mess);

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
