/*********
 By Alexandros Panagiotakopoulos
*********/

#include <ThingerESP32.h> //include the official Thinger.io library


#define USERNAME "USERNAME" //Enter your Thinger.io's account Username
#define DEVICE_ID "ESP32AMXXXX" //Enter your registered device ID
#define DEVICE_CREDENTIAL "ABCDEFGHJIJKLMNOPQSTYVWXYZ" //Enter your registered device credentials

#define SSID "XXXXXXXXXX" //Enter your Wi-Fi ID
#define SSID_PASSWORD "XXXXXXXXXXXXXX" //Enter your Wi-Fi password

int INTVALUE=1; //create a float number
float REALVALUE=1.11234; //create a real number 

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); //create a connection between the ESP32 & Thinger.io

void setup() {
  // open serial for debugging
  Serial.begin(115200); //intialize the serial baud rate to 115200 bauds/sec
  thing.add_wifi(SSID, SSID_PASSWORD); //establish the Wi-Fi connection
}

void loop() {
  thing.handle(); //handle the connection
  thing["VALUES EXAMPLE:"] >> [](pson& out){ //output into the Thinger.io API the sensor values
    out["INT VALUE = "] = INTVALUE; //output the int values
    out["REAL VALUE VALUE = "] = REALVALUE; //output the real values
    }; //output into the Thinger.io
INTVALUE++; //increase the integer value by +=1
REALVALUE++; //increase the real value by +=1
delay(1000); //wait for 1 second before running again!
  // Print a message into the Thinger.io API Console
}