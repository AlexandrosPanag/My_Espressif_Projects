#include "EspMQTTClient.h"

#define LED1 2  // define first led
#define LED2 3  // define second led

EspMQTTClient client(
  "",
  "",
  "mqttdashboard.com",
  "", "",
  "espclientID",
  1883
);

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud rate

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridden with enableHTTPWebUpdater
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  pinMode(LED1, OUTPUT); // Set LED1 pin as output
  pinMode(LED2, OUTPUT); // Set LED2 pin as output
  digitalWrite(LED1, LOW); // Initialize LED1 to LOW (off)
  digitalWrite(LED2, LOW); // Initialize LED2 to LOW (off)
}

void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  // client.subscribe("mytopic/test", [](const String & payload) {
  //  Serial.println(payload);
  // });

  // Example: Publish initial LED1 and LED2 status
  client.publish("mytopic/led1status", "OFF");
  client.publish("mytopic/led2status", "OFF");
}

void loop()
{
  static int cnt = 0; // Static variable to keep track of the count

  if(cnt % 2 == 0){
    digitalWrite(LED1, HIGH); // Turn on LED1
    client.publish("mytopic/led1status", "ON"); // Publish LED1 status
    digitalWrite(LED2, HIGH); // Turn on LED2
    client.publish("mytopic/led2status", "ON"); // Publish LED2 status
    delay(100); // Keep LEDs on for 100 milliseconds
  } else {
    digitalWrite(LED1, LOW);
    client.publish("mytopic/led1status", "OFF"); // Publish LED1 status
    digitalWrite(LED2, LOW); // Turn off LED2
    client.publish("mytopic/led2status", "OFF"); // Publish LED2 status
    delay(100); // Keep LEDs off for 100 milliseconds
  }
  client.loop(); // Call the loop function of EspMQTTClient to handle MQTT and WiFi tasks
  delay(5000); // Delay for 5 seconds before the next iteration
  cnt++; // Increment the count
}