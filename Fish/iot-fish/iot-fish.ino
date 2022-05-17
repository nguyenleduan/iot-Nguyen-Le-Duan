#include <OneButton.h>

#include <Servo.h>  
#include <DS3231.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// <---------Khai bao chan------>
const int minuteOnOff =2;
const int SA1trig = 11; // Chan 8 trig cua SA1
const int SA1echo = 11; // Chan 7 echo cua SA1
const int SA2trig= 13; // Chan 13 trig cua SA1
const int SA2echo= 12;  // Chan 12 echo cua SA2 
const int svPULLPin = 6; // chan Servo tha thuc an
const int svPUSHPin = 5; // chan Servo day thuc an
const int relayIn= 2;  // Chan relayIn 3
const int relayOut= 3;  // Chan relayOut 2 
const int ButtonMEnu = 8;  // Chan button menu 
const int ButtonControll = 7;  // Chan button controll 

const int valueMaxBox= 5;  // Khoang cach khi nuoc day box CM
const int valueMinBox= 20;  // Khoang cach khi nuoc day box CM 
// <---------khai bao bien------>
Servo svPush;
Servo svPULL ; 
LiquidCrystal_I2C lcd(0x27,16,2);  // khai bao lcd
DS3231 rtc(SDA,SCL); // thoi gian thuc 
Time time;    
OneButton buttonMEnu (ButtonMEnu,true);
OneButton buttonOK (ButtonControll,true); 
int menu = 0;
int menuChill = 0;
int btMenu = 0; 
int valueMenu = 0; 
const int SLDAY= 5;  // SO lan chay 

int ass = 1;
// <--------------------> 
void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
 Serial.print("\n----------Start-----------------"); 
  lcd.init();
//  svPULL.attach(svPULLPin); 
//  svPush.attach(svPUSHPin); 
  lcd.backlight(); 
  buttonMEnu.attachClick(funtionMenu);
  buttonOK.attachClick(funtionMenuChill);
//  SetLCD("HELLO",0,0,true);
  // pinMode(SA1trig, OUTPUT); //Chân trig xuất tín hiệu
  // pinMode(SA1echo, INPUT); 
//  pinMode(SA2trig, OUTPUT); //Chân trig xuất tín hiệu
//  pinMode(SA2echo, INPUT);    
//  pinMode(relayIn, OUTPUT);     
//  pinMode(relayOut, OUTPUT);    
//  digitalWrite(relayIn,0); // off relayIN 
//  digitalWrite(relayOut,0); // on relayOut  
   lcd.setCursor(1, 1);
   lcd.print("HELLO");
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
// thayNuoc(); 
  buttonMEnu.tick(); //Kiểm tra trạng thái nút nhấn 
  buttonOK.tick(); //Kiểm tra trạng thái nút nhấn 
//  Serial.print("Đếm xxx: "); 
//       lcd.setCursor(0, 0); // set vi tri show
//       lcd.print(" click :");  // noi dung     
//       delay(5000); 

//       lcd.clear();  

  delay(50);      

}
void funtionMenu(){ 
 Serial.print("\n--------2222222222222222222222222------------------"); 
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
             valueMenu = 9;
             SetLCD("> 6. Tro ve",0,0,true); 
             menu = 2;  
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
                break; 
            } 
        }
       }
} 
 void funtionMenuChill(){ 
                Serial.print("\n 11111111111111111111111"); 
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
                break;
            } 
            case 1:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 1"); 
                break;
            } 
            case 2:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 2"); 
                break;
            } 
            case 3:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 3"); 
                break;
            } 
            case 4:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 4"); 
                break;
            } 
            case 5:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 5"); 
                break;
            } 
            case 6:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 6"); 
                break;
            } 
            case 7:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 7"); 
                break;
            } 
            case 8:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 8"); 
                break;
            } 
            case 9:
            {  menu = 0; 
              btMenu = 0;
                Serial.print("\nĐếm xxx: 9"); 
                break;
            } 
        }
             
      funtionMenu();
  }
 }








void SetLCD(String mess, int hang, int cot, bool clear){
  if(clear){
    lcd.clear(); 
  } 
   lcd.setCursor(hang, cot);
   lcd.print(mess);

}

// void ChoAn(){
//   // check thức ăn
//   if(getKhoangCachSA(SA1trig,SA1echo)>5) { // 5 = khoảng cách thức ăn hết
//     DayThucAn();
//   }else{
//     // thông báo thức ăn hết
//     SetLCD("Het thuc an roi",0,0,true); 
//     SetLCD("Cho toi xin <3",0,0,false);
//   }
// }

// void DayThucAn(){ 
//   int i =0;
//   while(i<=SLDAY){ 
//     svPUSH.Write(40); 
//     delay(2000);
//     svPUSH.Write(130); 
//     delay(2000);
//     i++;
//   }else{ 
//   ThaThucAn();
//   }
// }
// void ThaThucAn(){
//     svPULL.Write(0); 
//     delay(1000);
//     svPULL.Write(90); 
//     delay(1000);
//     svPULL.Write(180); 
//     delay(1000);
//     svPULL.Write(0); 
//     delay(1000);
// }
void onclick(){
 Serial.print("Đếm 1: "); 
  int i =0; 
  while(i < 5){ 
      lcd.clear(); 
      lcd.setCursor(0, 0); // set vi tri show
      lcd.print(" DONE :");  // noi dung    
      lcd.setCursor(6, 0); // set vi tri show
      lcd.print(i);  // noi dung    
      lcd.setCursor(5, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA2trig,SA2echo));  // noi dung    
      delay(1000);  
      i++;
      lcd.clear();  
  }
      // lcd.setCursor(0, 0); // set vi tri show
      // lcd.print(" DONE :");  // noi dung    
      // lcd.setCursor(5, 1); // set vi tri show
      // lcd.print(getKhoangCachSA(SA2trig,SA2echo));  // noi dung    
      // delay(10000); 
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
