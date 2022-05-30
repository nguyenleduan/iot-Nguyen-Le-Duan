#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

void setup()
{ 
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("111112111111");
  lcd.setCursor(0,1);
  lcd.print("2222222222222");
}

void loop()
{
}
