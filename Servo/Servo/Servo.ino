#include <Servo.h>
int servoPin = 6;
int goc;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servoPin);
  Serial.println("--------------Start----------");
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(0);
  delay(1000);
  myServo.write(180); 
  delay(1000);
}
void ChoAn(){
  /
}
