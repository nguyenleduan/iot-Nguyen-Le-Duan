#include <OneButton.h>

#include <Servo.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// <---------Khai bao chan------>

const int SA1trig = 13;
const int SA1echo = 12;
const int SA2trig = 0; // Chan 13 trig cua SA1
const int SA2echo = 3; // Chan 12 echo cua SA2
const int svPULLPin = 10; // chan Servo tha thuc an
const int svPUSHPin = 9; // chan Servo day thuc an
const int relayIn = 0; // Chan relayIn 3
const int relayOut = 1; // Chan relayOut 2
const int ButtonMEnu = 2;  // Chan button menu
const int ButtonControll = 8;  // Chan button controll
const int MUOCMIN = 20;  // khoang cách nuoc thấm nhất
const int MUOCMAX = 5;  // khoang cách nuoc thấm nhất
#define lat 7
#define   clo 6
#define data 5
const int valueMaxBox = 5; // Khoang cach khi nuoc day box CM
const int valueMinBox = 20; // Khoang cach khi nuoc day box CM
// <---------khai bao bien------>
Servo svPush;
Servo svPULL ;
LiquidCrystal_I2C lcd(0x27, 16, 2); // khai bao lcd
DS3231 rtc(SDA, SCL); // thoi gian thuc
Time time;
OneButton buttonMEnu (ButtonMEnu, true);
OneButton buttonOK (ButtonControll, true);
int menu = 0;
int menuChill = 0;
int btMenu = 0;
int valueMenu = 0;
int ckickOK = 0;
const int SLDAY = 5; // SO lan chay

int ass = 1;
// <-------------------->
void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
  Serial.print("\n----------Start-----------------");

  lcd.init();
  pinMode(lat, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clo, OUTPUT);


  rtc.begin();
  lcd.backlight();
  lcd.setCursor(1, 1);
  lcd.print("HELLO");
  buttonMEnu.attachClick(funtionMenu);
  buttonOK.attachClick(funtionMenuChill);

  pinMode(SA1trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(SA1echo, INPUT);
  digitalWrite(lat, LOW);
  //  svPULL.attach(svPULLPin);
  //  svPush.attach(svPUSHPin);
  //  SetLCD("HELLO",0,0,true);
  //  pinMode(SA2trig, OUTPUT); //Chân trig xuất tín hiệu
  //  pinMode(SA2echo, INPUT);
  //  pinMode(relayIn, OUTPUT);
  //  pinMode(relayOut, OUTPUT);
  //  digitalWrite(relayIn,0); // off relayIN
  //  digitalWrite(relayOut,0); // on relayOut
}
void loop() {
  buttonMEnu.tick(); //Kiểm tra trạng thái nút nhấn
  buttonOK.tick(); //Kiểm tra trạng thái nút nhấn
  //  time = rtc.getTime();
  //  lcd.clear();
  //   lcd.setCursor(3, 0);
  //   lcd.print(time.hour);
  //   lcd.setCursor(6, 0);
  //   lcd.print(time.min);
  //   lcd.setCursor(9, 0);
  //   lcd.print(time.sec);
  //   lcd.setCursor(2, 1);
  //   lcd.print(getKhoangCachSA(SA1trig,SA1echo));
  //
  //   digitalWrite(lat,LOW);
  //   shiftOut(data,clo,LSBFIRST,0b00000000);
  //   digitalWrite(lat,HIGH);
  // get khoang cach SA1
  // int kc  = getKhoangCachSA(SA1trig,SA1echo);
  // get khoang cach SA2
  // int kc  = getKhoangCachSA(SA2trig,SA2echo);
  // ------------------------------------------------------------
  //   Serial.print("\nKhoảng cách: ");
  //   Serial.print(getKhoangCachSA(SA1trig,SA1echo));
  //   Serial.println(" cm\n");
  //   delay(1000);
  // thayNuoc();
  //  Serial.print("Đếm xxx: ");
  //       lcd.setCursor(0, 0); // set vi tri show
  //       lcd.print(" click :");  // noi dung
  //       delay(5000);
  //       lcd.clear();
}



void funtionMenu() {
  lcd.clear();
  Serial.print("\n");
  Serial.print(getKhoangCachSA(SA1trig, SA1echo));
  ckickOK = 1;
  if (btMenu == 1) {
    switch (menu)
    {

      /* 
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
      */
      ////////// NUOC //////////
      case 2:
        {
          valueMenu = 1;
          SetLCD("> 1. Thay nuoc", 0, 0, true);
          SetLCD("  2. Them nuoc", 0, 1, false);
          // thay nuoc
          menu = 4;
          break;
        }
      case 4:
        {
          valueMenu = 2;
          SetLCD("> 2. Them nuoc", 0, 0, true);
          SetLCD("  3. Xa nuoc", 0, 1, false);
          menu = 5;
          break;
        }
      case 5:
        {
          valueMenu = 3;
          SetLCD("> 3. Xa nuoc", 0, 0, true);
          SetLCD("  4. Xa nuoc 10s", 0, 1, false);
          menu = 6;
          break;
        }
      case 6:
        {
          valueMenu = 4;
          SetLCD("> 4. Xa nuoc 10s", 0, 0, true);
          SetLCD("  5. Tro ve", 0, 1, false);
          menu = 7;
          break;
        }
      case 7:
        {
          valueMenu = -1;
          SetLCD("> 5. Tro ve", 0, 0, true);
          menu = 2;
          break;
        }
      ////////// Thuc An  //////////
      case 3:
        {
          valueMenu = 5;
          SetLCD("> 1. Cho an", 0, 0, true);
          SetLCD("  2. Day TA 5L", 0, 1, false);
          menu = 8;
          break;
        }
      case 8:
        {
          valueMenu = 6;
          SetLCD("> 2. Day TA 5L", 0, 0, true);
          SetLCD("  3. Day TA 10L", 0, 1, false);
          menu = 9;
          break;
        }
      case 9:
        {
          valueMenu = 7;
          SetLCD("> 4. Day TA 10L", 0, 0, true);
          SetLCD("  5. Tha thuc an", 0, 1, false);
          menu = 10;
          break;
        }
      case 10:
        {
          valueMenu = 8;
          SetLCD("> 5. Tha thuc an", 0, 0, true);
          SetLCD("  6. Tro ve", 0, 1, false);
          menu = 11;
          break;
        }
      case 11:
        {
          SetLCD("> 6. Tro ve", 0, 0, true);
          menu = 3;
          valueMenu = -1;
          break;
        }
      // setup

      case 100:
        {
          SetLCD("> 1. Auto 4d", 0, 0, true);
          SetLCD("  2. Auto 7d", 0, 1, false);
          menu = 101;
          valueMenu = 100;
          break;
        }
      case 101:
        {
          SetLCD("> 2. Auto 7d", 0, 0, true);
          SetLCD("  3. Auto 9d", 0, 1, false);
          menu = 102;
          valueMenu = 101;
          break;
        }
      case 102:
        {
          SetLCD("> 3. Auto 9d", 0, 0, true);
          SetLCD("  4. Stop AUTO", 0, 1, false);
          menu = 103;
          valueMenu = 102;
          break;
        }
      case 103:
        {
          SetLCD("> 4. Stop AUTO", 0, 0, true); 
          SetLCD("  5. Tro ve", 0, 1, false);
          menu = 104;
          valueMenu = 103;
          break;
        }
      case 104:
        {
          SetLCD("> 5. Tro ve", 0, 0, true);
          menu = 100;
          valueMenu = -1;
          break;
        }
    }
  } else {
    switch (menu)
    {
      case 0:
        {
          SetLCD("---MENU---", 3, 0, true);
          SetLCD("  1. Nuoc", 0, 1, false);
          menu = 1;
          break;
        }
      case 1:
        {
          // NUOC
          ckickOK == 1;
          SetLCD("> 1. Nuoc", 0, 0, true);
          SetLCD("  2. Thuc an ", 0, 1, false);
          menu = 2;
          break;
        }
      case 2:
        {
          // Thuc an
          ckickOK == 1;
          SetLCD("> 2. Thuc an", 0, 0, true);
          SetLCD("  3. Tro ve", 0, 1, false);
          menu = 3;
          break;
        }
      case 3:
        {
          // Set time
          ckickOK == 1;
          SetLCD("> 3. Setup", 0, 0, true);
          SetLCD("  4. Tro ve", 0, 1, false);
          menu = 100;
          break;
        }
      case 100:
        {
          // tro ve
          ckickOK == 1;
          SetLCD("> 4. Tro ve", 0, 0, true);
          SetLCD("---MENU---", 3, 1, false);
          menu = 1;
          valueMenu = -1;
          break;
        }
    }
  }
}

void SetRelay(bool in, bool out) {
  digitalWrite(lat, LOW);
  if (in && out) {
    // on all
    shiftOut(data, clo, LSBFIRST, 0b00000000);

  } else if (!in && !out) {
    //off all
    shiftOut(data, clo, LSBFIRST, 0b11111111);
  } else {
    if (in) {
      // in on
      shiftOut(data, clo, LSBFIRST, 0b00111111); // relay in on
    } else {
      if (out) {
        // out on
        shiftOut(data, clo, LSBFIRST, 0b11011011); // relay in on
      }
    }
  }
  digitalWrite(lat, HIGH);
}
void funtionMenuChill() {

  if (ckickOK == 0) {

  } else {
    btMenu = 1;
    int index = 0;
    switch (valueMenu)
    {
      case -1:
        {
          menu = 0;
          valueMenu = 0;
          btMenu = 0;
          SetLCD("Xin cam on <3", 0, 0, true);
          delay(1000);

          digitalWrite(lat, LOW);
          shiftOut(data, clo, LSBFIRST, 0b00000000);
          digitalWrite(lat, HIGH);
          lcd.clear();
          break;
        }
      case 1:
        {
          ckickOK = 0;
          valueMenu = 0;
          menu = 0;
          btMenu = 0;
          index = 1;
          SetLCD("Dang thay nuoc...", 0, 0, true);
          delay(1000);
          thayNuoc();
          break;
        }
      case 2:
        {
          ckickOK = 0;
          valueMenu = 0;
          menu = 0;
          btMenu = 0;
          index = 1;
          SetLCD("Dang them nuoc...", 0, 0, true);
          delay(1000);
          break;
        }
      case 3:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Dang xa nuoc...", 0, 0, true);
          delay(1000);
          break;
        }
      case 4:
        {
          ckickOK = 0;
          menu = 0;
          valueMenu = 0;
          btMenu = 0;
          index = 1;
          SetLCD("Dang xa 30s...", 0, 0, true);
          delay(1000);
          break;
        }

      /// cho an
      case 5:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Dang cho an...", 0, 0, true);
          delay(1000);
          break;
        }
      case 6:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Dang day TA...", 0, 0, true);
          delay(1000);
          break;
        }
      case 7:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Dang day TA...", 0, 0, true);
          delay(1000);
          break;
        }
      case 8:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Dang tha TA...", 0, 0, true);
          delay(1000);
          break;
        }
      case 100:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Da setup 4d", 0, 0, true);
          delay(1000);
          break;
        }
      case 101:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Da setup 7d", 0, 0, true);
          delay(1000);
          break;
        }
      case 102:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Da setup 9d", 0, 0, true);
          delay(1000);
          break;
        } 
      case 103:
        {
          ckickOK = 0;
          menu = 0;
          btMenu = 0;
          valueMenu = 0;
          index = 1;
          SetLCD("Stop AUTO", 0, 0, true);
          delay(1000);
          break;
        }
    }
    if (index == 0) {
      funtionMenu();
    }
  }
}








void SetLCD(String mess, int hang, int cot, bool clear) {
  if (clear) {
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
void onclick() {
  Serial.print("Đếm 1: ");
  int i = 0;
  while (i < 5) {
    lcd.clear();
    lcd.setCursor(0, 0); // set vi tri show
    lcd.print(" DONE :");  // noi dung
    lcd.setCursor(6, 0); // set vi tri show
    lcd.print(i);  // noi dung
    lcd.setCursor(5, 1); // set vi tri show
    lcd.print(getKhoangCachSA(SA2trig, SA2echo)); // noi dung
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

int getKhoangCachSA(int trig, int echo) {
  //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig, 0); //Tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig, 0);
  return int ( pulseIn (echo, HIGH) / 2 / 29.412); // trả về khoảng cách CM
}
void thayNuoc() {
  SetLCD("Dang thay nuoc", 0, 0, true);
  SetLCD("Vui long cho !", 0, 1, false);
  int isNuocIn = 0;
  SetRelay(false, true); // xa nuoc
  SetLCD("xa nuoc: ON", 0, 0, true);
  SetLCD("them nuoc: OFF", 0, 1, false);
  delay(5000); /// xa nuoc 5s
  SetRelay(false, false); // ngung xa nuoc
  SetLCD("xa nuoc: OFF", 0, 0, true);
  SetLCD("them nuoc: OFF", 0, 1, false);
  delay(2000);
  isNuocIn = getKhoangCachSA(SA1trig, SA1echo); // khoang cach khi xa nuoc
  SetRelay(true, false); // them nuoc vao
  SetLCD("xa nuoc: OFF", 0, 0, true);
  SetLCD("them nuoc: ON", 0, 1, false);
  delay(5000); /// them nuoc trong 5s
  SetRelay(false, false); // ngung xa nuoc
  SetLCD("xa nuoc: OFF", 0, 0, true);
  SetLCD("them nuoc: OFF", 0, 1, false);
  if (getKhoangCachSA(SA1trig, SA1echo) <= isNuocIn) {
    SetLCD("Dang thay nuoc...", 0, 0, true);
    SetLCD("Vui long cho....", 0, 1, false);
    delay(1000);
    // co nuoc
    SetRelay(false, true); // xa nuoc
    while (getKhoangCachSA(SA1trig, SA1echo) <= MUOCMIN ) {   // neu nuoc chưa đủ thì => xa tiep tuc
      SetLCD("Dang thay nuoc...", 0, 0, true);
      lcd.setCursor(0, 1); // set vi tri show
      lcd.print("Muc nuoc: "); // noi dung
      lcd.setCursor(10, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA1trig, SA1echo)); // noi dung doi ra  % 
      digitalWrite(lat, LOW);
      shiftOut(data, clo, LSBFIRST, 0b11000000);
      digitalWrite(lat, HIGH);
      delay(1000);
      SetRelay(false, true); // xa nuoc
    }
    // them nuoc
    SetRelay(true, true); // xa  & them nuoc
    delay(5000); // rua ong nuoc 5s
    SetRelay(true, false); // thêm  nuoc
    // check muc nuoc
    while (getKhoangCachSA(SA1trig, SA1echo) >= MUOCMAX ) {
      SetLCD("Dang them nuoc...", 0, 0, true);
      lcd.setCursor(0, 1); // set vi tri show
      lcd.print("Muc nuoc: "); // noi dung
      lcd.setCursor(10, 1); // set vi tri show
      lcd.print(getKhoangCachSA(SA1trig, SA1echo)); // noi dung doi ra  % 
      digitalWrite(lat, LOW);
      shiftOut(data, clo, LSBFIRST, 0b00100110); // relay in on
      digitalWrite(lat, HIGH);
      delay(1000);
      SetRelay(true, false); // xa nuoc
    }

    SetRelay(false, false); // thêm  nuoc
    SetLCD("Hoanh thanh", 0, 0, true);
    SetLCD("Xin cam on!", 0, 1, false);
  }
}
