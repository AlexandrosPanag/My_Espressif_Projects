//Code written by Alexandros Panagiotakopoulos
//alexnadrospanag.github.io
//DATE: 28/05/2025

#include "EspMQTTClient.h"


EspMQTTClient client(
  "",              // wifi SSID
  "",                          // wifi password
  "mqttdashboard.com",         // MQTT Broker server ip (broker.mqttdashboard.com for example)
  "",                          // MQTT Username: Can be omitted if not needed
  "",                          // MQTT Password: Can be omitted if not needed
  "espclientID",               // Client name that uniquely identify your device
  1883                         // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200); // Start serial communication at 115200 baud rate

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("mytopic/test", [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });

  // Publish a message to "mytopic/test"
  client.publish("mytopic/test", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  });
}

void loop() // This function is called repeatedly
{
  client.loop(); // Call the loop function of EspMQTTClient to handle MQTT and WiFi tasks
}
