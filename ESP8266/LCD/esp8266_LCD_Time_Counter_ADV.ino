/*********
 By Alexandros Panagiotakopoulos
*********/

#include <LiquidCrystal_I2C.h>



// set the LCD number of columns and rows
int time_count_second=0; //Declaring a time counter for each second
int minutes_elapsed=0; //Declaring minutes elapsed
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
  lcd.clear();
  //random number generator
   time_count_second++; //adding each second on the time counter
    
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(time_count_second);

  lcd.setCursor(8,0); //display "SEC" message which translates to "seconds elapsed"
  lcd.print("SEC");

  
  // clears the display to print new message
  if(time_count_second==60){
    time_count_second=0; //reset the second counter
    minutes_elapsed++;  //increase the minute elapsed by +1 , 60 seconds = 1 minute
    }
  lcd.setCursor(0,1);
  lcd.print(minutes_elapsed);

  lcd.setCursor(8,1); //display "MIN" message which translates to "minutes elapsed"
  lcd.print("MIN");
  delay(1000); //delay 1 second
}
