#define lat 7
#define   clo 6
#define data 5
// cl lat data
int timeCho = 1000;
unsigned long hienTai = 0;
unsigned long thoiGian;
// 0xc0 | 0xf9 | 0xa4 | 0xb0 | 0x99 | 0x92 | 0x82 | 0xf8 | 0x90 | 0xff
byte led = 0;
void setup() {
  Serial.begin(9600);//Mở cổng Serial ở 9600
  pinMode(lat, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clo, OUTPUT);
  Serial.print(" a -------------------------start----------\n");

} 
void delays(){
  thoiGian = millis();
  while(thoiGian - hienTai > timeCho){
    hienTai =  millis();
    
  Serial.print("  --------------------^^^^^^^^^----------\n");
  }
}
void loop() {
 
  Serial.print(" a -------------------------!!!!----------\n");
//  delays();

    digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11111111);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11111110);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11111100);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11111000);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11110000);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11100000);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b11000000);
   digitalWrite(lat,HIGH);
   delay(1000);  
   digitalWrite(lat,LOW);
   shiftOut(data,clo,LSBFIRST,0b10000000);
   digitalWrite(lat,HIGH);
     delay(1000);  
     digitalWrite(lat,LOW);
     shiftOut(data,clo,LSBFIRST,0b00000000);
     digitalWrite(lat,HIGH);
   delay(1000);  
}
void leds (){
  while(true){
  }
}
