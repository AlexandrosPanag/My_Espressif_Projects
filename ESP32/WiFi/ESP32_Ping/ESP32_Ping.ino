/*********
 By Alexandros Panagiotakopoulos
*********/

#include <WiFi.h> //include the wifi library
#include <ESP32Ping.h> //include the ESP32 Ping library https://github.com/marian-craciunescu/ESP32Ping --note that this is a library port
//from the official ESP8266Ping library.

 // Please support the original library authors!
 
const char* ssid = "yourNetworkName"; //enter your hotspot id
const char* password =  "yourNetworkPass"; //enter your hotspot password
 
void setup() { //setup point
  Serial.begin(9600); //initialize the serial baud rate to 9600 bauds
 
  WiFi.begin(ssid, password); //begin the wifi connection
   
  while (WiFi.status() != WL_CONNECTED) { //while the wifi is connected
    delay(500); //delay approximately half a second
    Serial.println("Connecting to WiFi..."); //print a message into the Serial port
  }
 
  bool success = Ping.ping("www.github.com", 3); //try to ping the github's official website
  if(!success){ //check if the ping was successful --if it wasn't
    Serial.println("Ping failed"); //then print ping failed
    return; //return the status
  }
  Serial.println("Ping succesful."); //otherwise if the ping was successful print the appro
}
 
