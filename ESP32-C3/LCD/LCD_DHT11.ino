/*********
 By Alexandros Panagiotakopoulos
*********/

// connect the sensor with the LCD DISPLAY: 
// DHT11             ESP32C3 DEVKITC-02
// left sensor pin   D4
// VDD/VIN           DIGITAL 3V3
// GND               DIGITAL GND
// ------------------------------------------
// LCD               ESP32C3 DEVKITC-02
// VCC               5V
// GND               DIGITAL GND
// SDA PIN 8         SDA
// SCL PIN 9         SCL
//-------------------------------------------


// Original Source was taken from : https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - LiquidCrystal I2C Author: Frank de Brabander : https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/
// Please support the original library authors!
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4     // connect to the D4
#define DHTTYPE DHT11   // declare the DHT 11 sensor type

// set the LCD number of columns and rows
int lcdColumns = 16; //set the LCD number of columns
int lcdRows = 2; //set the lcd number of rows

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

DHT dht(DHTPIN, DHTTYPE); //declare the DHT PIN, WITH THE TYPE (INITIALIZE THE DHT11 SENSOR)

void setup() {
  Serial.begin(9600); //initialize the serial baud rate to 9600 bauds per second
  lcd.init(); //initialize the LCD display                     
  lcd.backlight();  // turn on LCD backlight 
  dht.begin(); //begin taking temperature measurements
}

void loop() {
  delay(1000);   // Wait a second between measurements.
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) { //if the value reading failed
    Serial.println(F("Failed to read from DHT sensor!")); //then print the right message into the Serial Port 
    lcd.setCursor(0, 0); //also set the cursor to first column, first row 
    lcd.print("FAILURE"); //print the right message into the LCD Display
    return; 
  }

  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  lcd.print(t);   // print the temperature
  lcd.setCursor(0,1); //set the cursor to the first column, second row
  lcd.print("Celsius"); //print the right message into the Serial port
    // clears the display to print new message
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
    // clears the display to print new message
  delay(10000); //delay 10 seconds before clearing the lcd display (taking another measurement)
  lcd.clear(); //clear the LCD Display
}
