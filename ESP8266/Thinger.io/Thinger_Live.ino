/*********
 By Alexandros Panagiotakopoulos
*********/

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h> //include the neccessary libraries

#define USERNAME "myusername" //define your username's password from thinger.io
#define DEVICE_ID "mydeviceid" //define your device's id from thinger.io
#define DEVICE_CREDENTIAL "myrandomlygeneratedcredentials" //define your randomly generated credentials from thinger.io

#define SSID "myrouterid" //define your router's id
#define SSID_PASSWORD "myrouterpassword" //define your router's password


ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); //generate a connection

void setup() {
  pinMode(0, OUTPUT); //set D0 as an output
  Serial.begin(9600); //begin the baud rate to 9600 bauds
  thing.add_wifi(SSID, SSID_PASSWORD); //add the wi-fi password
  thing["0"] << digitalPin(0); //create a data output from D0
}

void loop() {
  thing.handle(); //generate the connection
}
