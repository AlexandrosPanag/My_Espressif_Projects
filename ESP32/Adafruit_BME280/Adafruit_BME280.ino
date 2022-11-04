/*********
 Created By Alexandros Panagiotakopoulos
 Based on the work of the official Adafruit BME280 official library example
*********/


//Include all the necesary libraries - Please support the work of the original library authors
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>

//In case the Pins do not work on your current model try using the ESP32 SPI Debug at 
// https://github.com/AlexandrosPanag/My_ESP32_Projects/tree/main/DEBUG/SPI_DEBUG
#define BME_SCK 18 //BME SCK -> ESP32 PIN 18
#define BME_MISO 19 //BME SD0 -> ESP32 PIN 19
#define BME_MOSI 23 // BME SDI -> ESP32 PIN 23
#define BME_CS 5 //BME CS -> ESP32 PIN 5

#define SEALEVELPRESSURE_HPA (1013.25)


//create the Adafruit BME Object
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); //connect the BME280 Sensor based on the above mentioned pin locations


void setup() {
  Serial.begin(9600); //Intialize Serial Baud Rate to 9600 Bauds/Second
  Serial.println(F("BME280 test"));

  bool status; //check the status of the BME280 sensor

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println();
}


void loop() { 
  printValues();
  delay(1000);
}

void printValues() {

  //Print the Temperature
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  //Print the Pressure Above the Sea Level
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  //Print the Approximate Level Sea Level Pressure
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  //Print the Humidity 
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
  delay(1000); //delay approx. 1 second
}
