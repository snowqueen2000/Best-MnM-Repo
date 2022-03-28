/* 
MEEN 3230 I2C LCD test code 
This code will scan a character back and forth across the first line of a 16x2 I2C enabled LCD screen  
It is to demonstrate the method of writing data to the I2C LCD screen.  
This code uses the I2C library which accesses the SDA and SCL Pins with are clones of A4 and A5 pins on the Arduino board.  
You cannot simultaneously use both the A4 and A5 pins and the SDA and SCL pins unless they are connecting to two different I2C devices with two separate addresses.  
*/ 

#include <Wire.h>  // This is the standard I2C library it uses the built in SDA and SCL pins  
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display 

int delayTime = 500; 

void setup() { 
  lcd.init();                      // initialize the lcd 
  lcd.backlight();                 // turn on LCD backlight 
  clearLCD;                        // clear the LCD 
} 

void loop() { 
  lcd.setCursor(0,1); 
  lcd.print("There,          "); 

  for (int i = 0; i < 16; i++) { 
    lcd.setCursor(i, 0); 
    lcd.print(" >"); 
    delay(delayTime); 
  } 

  lcd.setCursor(0,1); 
  lcd.print("and Back Again! "); 

  for (int i = 15; i >= 0; i--) { 
    lcd.setCursor(i, 0); 
    lcd.print("< "); 
    delay(delayTime); 
  } 
} 

void clearLCD() { 
  // Clear any characters on the screen.  
  lcd.setCursor(0, 0);            // move to the first character of the first line 
  lcd.print("                ");  // write sixteen blank spaces 
  lcd.setCursor(0, 1);            // move to the first character of the second line 
  lcd.print("                ");  // write sixteen blank spaces  
}   
