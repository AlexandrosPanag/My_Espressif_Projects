/*********
 By Alexandros Panagiotakopoulos
*********/

#include <LiquidCrystal_I2C.h>



// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  //random number generator from [0...100]
   for(int i=1; i <=9; i++){
    int r=random(0,100);
    Serial.print(r);
    Serial.print(" ");  
    Serial.println();
    
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(r);
  delay(10000); //delay for 10 seconds
  lcd.clear(); // clears the display to print new message
   }
}
