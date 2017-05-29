#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  lcd.begin(16,2);
  lcd.backlight();

  lcd.home ();                   // go home
  lcd.print("Setup ... ");
  lcd.setCursor ( 0, 1 );        // go to the next line
  delay(500);
  lcd.print ("Snackerator 9000");
  delay(500);
}

void loop()
{ 

  lcd.clear();
  fadeLeft("please work!");
  fadeRight("why git no work?!!");
}


void fadeLeft(String msg1){
  fadeLeft(msg1, "");
}

void fadeLeft(String msg1, String msg2){
  lcd.clear();
  lcd.home ();
  lcd.print (msg1);
  lcd.setCursor ( 0, 1 );
  lcd.print (msg2);
  delay(700);

  for(int i = 0; i < 16; i++){
    lcd.scrollDisplayLeft();  
    delay(100);
  }  
}

void fadeRight(String msg1){
  fadeRight(msg1, "");
}

void fadeRight(String msg1, String msg2){
  lcd.clear();
  lcd.home ();
  lcd.print (msg1);
  lcd.setCursor ( 0, 1 );
  lcd.print (msg2);
  delay(700);

  for(int i = 0; i < 16; i++){
    lcd.scrollDisplayRight();  
    delay(100);
  }  
}
