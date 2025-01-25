## DHT11 WiFi Server ESP8266


## Overview

This project is designed to run on an ESP8266 microcontroller. It reads temperature and humidity data from a DHT11 sensor, handles client connections, and sends the sensor readings to the client.

## Author

- **Name**: Alexandros Panagiotakopoulos
- **Website**: [alexandrospanag.github.io](https://alexandrospanag.github.io)
- **Date**: January 2025
  
License
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

## Libraries
- **DHT**: For reading data from the DHT11 sensor.
- **WiFi**: For connecting to WiFi networks.
- **WiFiClient**: For handling client connections.

## Pin Definitions
- **DHTPIN**: Pin connected to the DHT11 sensor (GPIO2).
- **DHTTYPE**: Type of DHT sensor (DHT11).
- **LED_BUILTIN**: Onboard LED pin.
- **Pin 4**: Connected to D2.
- **Pin 0**: Connected to D3.

##Constants

- **ssid:** SSID of the WiFi network.
- **password:** Password of the WiFi network.
- **maxReadings:** Maximum number of sensor readings to store.

## Variables

- **temperatures**: Array to store the temperature readings.
- **timestamps**: Array to store the timestamps of the readings.
- **currentIndex**: Index to store the current reading.
- **server**: WiFi server running on port 80.
- **dht**: DHT sensor object.

## Functions

### `void setup()`

The setup function initializes the serial communication, sets up the pin modes, starts the DHT sensor, and connects to the WiFi network.

### `void loop()`

The loop function continuously reads temperature and humidity data from the DHT11 sensor, stores the readings, and handles client connections to send the sensor data.

**Key Operations:**

-Reads temperature and humidity data from the DHT11 sensor.
-Checks for failed sensor readings and handles errors.
-Computes the heat index in both Fahrenheit and Celsius.
-Stores the current temperature and timestamp in arrays.
-Handles client connections and sends the stored sensor data.
-float readTemperature()
-The readTemperature function reads the temperature from the DHT11 sensor and returns it.

### float readHumidity()
The readHumidity function reads the humidity from the DHT11 sensor and returns it.

float computeHeatIndex(float temperature, float humidity, bool isFahrenheit)
The computeHeatIndex function computes the heat index based on the temperature and humidity readings.

### Usage

Client Connection: The ESP8266 waits for a client to connect. Once connected, it sends the stored sensor readings to the client.
Data Transmission: The sensor readings include a timestamp and temperature. The data is sent every second.
Error Handling: If the sensor readings fail, an error message is printed, and the LEDs are turned off.
Heat Index Calculation: The heat index is computed in both Fahrenheit and Celsius.
Temperature Check: The temperature is checked, and appropriate messages are printed. LEDs are turned on or off based on the temperature.
Example Output

## Example Code

```cpp
// By Alexandros Panagiotakopoulos
// alexandrospanag.github.io
// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

// Date: January 2025

#include "DHT.h" // Include the DHT library
#include <WiFi.h> // Include the Wi-Fi library
#include <WiFiClient.h> // Include the Wi-Fi client library
 
const char *ssid = "yourwifiroutername"; // SSID of the network
const char *password = "mypassword"; // Password of the network

WiFiServer server(80); // Create a server object

const int maxReadings = 20; // Maximum number of readings to store
float temperatures[maxReadings]; // Array to store the temperatures
unsigned long timestamps[maxReadings]; // Array to store the timestamps
int currentIndex = 0; // Index to store the current reading

#define DHTPIN 2     // Connect to the D4 (GPIO2)
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

void setup() {
  Serial.begin(9600); // Start the serial communication
  Serial.println(F("DHT11 test!")); // Print a message
  pinMode(LED_BUILTIN, OUTPUT); // Connect to the onboard LED
  pinMode(4, OUTPUT); // Connect to D2
  pinMode(0, OUTPUT); // Connect to D3
  dht.begin(); // Start the DHT sensor
  
  // Connect to WiFi
  Serial.print("Connecting to "); // Print a message
  Serial.println(ssid); // Print the SSID
  WiFi.begin(ssid, password); // Connect to the network

  while (WiFi.status() != WL_CONNECTED) { // Wait for the connection
    delay(100); // Wait for the connection
  }
  Serial.println(""); // Print a blank line
  Serial.println("WiFi connected."); // Print a message
  Serial.println("IP address: "); // Print the IP address
  Serial.println(WiFi.localIP()); // Print the IP address

  server.begin(); // Start the server
}

void loop() {
  // Wait two seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) { // Check if any reads failed
    Serial.println(F("Failed to read from DHT sensor!")); // Print a message
    digitalWrite(LED_BUILTIN, HIGH); // Turn off the LED
    digitalWrite(4, HIGH); // Turn off the LED
    digitalWrite(0, HIGH); // Turn off the LED
    delay(100); // Wait for 100 milliseconds
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahrenheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Store the current temperature and timestamp in the arrays
  temperatures[currentIndex] = t; // Store the temperature
  timestamps[currentIndex] = millis(); // Store the timestamp
  currentIndex = (currentIndex + 1) % maxReadings; // Circular buffer

  if (t > 15) { // Check the temperature
    Serial.println("High temperature!"); // Print a message
    digitalWrite(LED_BUILTIN, LOW); // Turn on the LED
    digitalWrite(4, HIGH); // Turn on the LED
    digitalWrite(0, LOW); // Turn off the LED
    delay(100);
  } else if (t > 10) {
    Serial.println("Medium temperature!"); // Print a message
    digitalWrite(LED_BUILTIN, LOW); // Turn on the LED
    digitalWrite(4, LOW); // Turn off the LED
    digitalWrite(0, HIGH); // Turn on the LED
    delay(100); // Wait for 100 milliseconds
  } else {
    Serial.println("Low temperature!"); // Print a message
    digitalWrite(LED_BUILTIN, HIGH); // Turn off the LED
    digitalWrite(4, LOW); // Turn off the LED
    digitalWrite(0, LOW); // Turn off the LED
    delay(100); // Wait for 100 milliseconds
  }

  Serial.print(F("Humidity: ")); // Print a message
  Serial.print(h); // Print the humidity
  Serial.print(F("%  Temperature: ")); // Print a message
  Serial.print(t); // Print the temperature
  Serial.print(F("°C ")); // Print a message
  Serial.print(f); // Print the temperature in Fahrenheit
  Serial.print(F("°F  Heat index: ")); // Print a message
  Serial.print(hic); // Print the heat index
  Serial.print(F("°C ")); // Print a message
  Serial.print(hif); // Print the heat index in Fahrenheit
  Serial.println(F("°F")); // Print a message

  // Handle client connections
  WiFiClient client = server.available(); // Check if a client has connected
  if (client) {
    Serial.println("New Client."); // Print a message when a new client is connected
    client.println("HTTP/1.1 200 OK"); // Send a 200 OK response
    client.println("Content-type:text/html"); // Set the content type
    client.println(); //  Important: End of headers

    while (client.connected()) {
      // Send all stored values to the client
      for (int i = 0; i < maxReadings; i++) { // Iterate over all the values
        if (timestamps[i] != 0) { // Check if the value is valid
          client.print("<b>Timestamp: </b>"); // Send a bold text
          client.print(timestamps[i]); // Send the timestamp
          client.print(" ms - <b> Temperature: </b>"); // Send a bold text
          client.print(temperatures[i]); // Send the temperature
          client.print(" °C<br>"); // Send a line break
        }
      }
      client.println(); // Send a blank line
      delay(1000); // Send data every second
    }
    client.stop(); // Close the connection
    Serial.println("Client Disconnected."); // Print a message when the client is disconnected
  }
  delay(1000); // Wait for 1 second
}





