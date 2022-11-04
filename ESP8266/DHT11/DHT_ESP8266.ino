/*********
 By Alexandros Panagiotakopoulos
*********/

// connect the sensor : 
// DHT11             ESP8266
// left sensor pin   D4
// VDD/VIN           DIGITAL 3V
// GND               DIGITAL G


#include "dht.h" 
dht DHT;

void setup(){
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 }//end "setup()"
 
void loop(){
    DHT.read11(2); //read from D4
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity); 
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(5000);//Wait 5 seconds before accessing sensor again.
  //Fastest should be once every two seconds.
}// end loop() 
