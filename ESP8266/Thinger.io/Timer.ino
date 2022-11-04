/*********
 By Alexandros Panagiotakopoulos
*********/

#include <SPI.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h> //include the neccessary libraries

//Thinger Config
#define USERNAME "" //define your username's password from thinger.io
#define DEVICE_ID "ESP8266" //define your device's id from thinger.io
#define DEVICE_CREDENTIAL "" //define your randomly generated credentials from thinger.io

#define SSID "" //define your router's id
#define SSID_PASSWORD "" //define your router's password


int time_count_second=0; //declaring a global counter variable


// thinger.io config
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); //generate a connection

void setup() {
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD); //add the wi-fi password
  thing["Timer:"] >> [](pson& out){ //handle the app connection
    out["Time running"] = time_count_second; //take an output with the time running from your system
  };
}

void loop() {
  time_count_second++; //adding approximately that 1 second has passed
  Serial.println(time_count_second);  //print the total time elapsed 
  thing.handle(); //handle the thinger.io connection
  delay(1000); //adding 1 second refresh rate
}
