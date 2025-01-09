/*********
 By the Autonomous Systems Laboratory 2022-2023, for the Department of Informatics & Telecommunications
 Lesson "Internet of Things" Computer System Courses Flow of the 7th Semester
*********/


// connect the sensor : 
// DHT11             ESP32
// left sensor pin   D4
// VDD/VIN           DIGITAL 3V3
// GND               DIGITAL GND

// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// Please support the original library authors!

#include "DHT.h" //include the DHT.h sensor library

#define DHTPIN 4     // connect to the D4

#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE); //Declare the dht sensor as an object

void setup() {
  Serial.begin(9600); //Initialize the Serial Port baud rate to 9600 bauds
  dht.begin(); //Begin taking measurements (Humidity, Temperature, Heat Index)
}

void loop() {
  // Wait a second between measurements.
  delay(1000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
   //print the Humidity into the Serial Port
  Serial.print(F("Humidity: "));
  Serial.print(h);

  //print the Temperature into the Serial Port 
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}