## HC_SR04 WiFi Freenove


## Overview

This project is designed to run on an ESP32C3 microcontroller. It handles client connections, sends stored sensor readings to the client, and categorizes distances into different categories based on predefined thresholds.

## Author

- **Name**: Alexandros Panagiotakopoulos
- **Website**: [alexandrospanag.github.io](https://alexandrospanag.github.io)
- **Date**: January 2025

## Libraries

- **WiFi**: For connecting to WiFi networks.
- **WiFiClient**: For handling client connections.
- **Freenove_WS2812_Lib_for_ESP32**: For controlling WS2812 LEDs.

## Pin Definitions

- **LEDS_COUNT**: Number of LEDs.
- **LEDS_PIN**: Pin connected to the LEDs.
- **CHANNEL**: Channel for the LEDs.
- **trigPin**: Pin connected to the trigger of the ultrasonic sensor.
- **echoPin**: Pin connected to the echo of the ultrasonic sensor.

## Constants

- **ssid**: SSID of the WiFi network.
- **password**: Password of the WiFi network.
- **maxReadings**: Maximum number of sensor readings to store.

## Variables

- **distances**: Array to store the distance readings.
- **timestamps**: Array to store the timestamps of the readings.
- **currentIndex**: Index to store the current reading.
- **server**: WiFi server running on port 80.
- **strip**: WS2812 LED strip object.

## Functions

### `void setup()`

The `setup` function initializes the serial communication, sets up the pin modes, and connects to the WiFi network.

### `void loop()`

The `loop` function continuously checks for client connections and sends stored sensor readings to the connected client. It also categorizes the distances and sends the categorized data.

**Key Operations:**
- Iterates over stored sensor readings.
- Sends timestamp, distance, and categorized distance to the client.
- Waits for 1 second before sending the next set of data.
- Closes the client connection and prints a message when the client disconnects.

### `String categorizeDistance(long distance)`

The `categorizeDistance` function categorizes a given distance into one of three categories: "Near", "Medium", or "Far".

**Parameters:**
- `distance` (long): The distance value to be categorized.

**Returns:**
- `String`: The category of the distance ("Near", "Medium", or "Far").

## Example Code

```cpp
// By Alexandros Panagiotakopoulos
// alexandrospanag.github.io
// Date: January 2025

#include <WiFi.h> // Include the WiFi library
#include <WiFiClient.h> // Include the WiFiClient library
#include "Freenove_WS2812_Lib_for_ESP32.h" // Include the WS2812 library

// Freenove Pin Definitions
#define LEDS_COUNT  1
#define LEDS_PIN    8
#define CHANNEL     0

const char *ssid = "A14"; // SSID of the network
const char *password = "mypassword"; // Password of the network

WiFiServer server(80); // Create a server on port 80

const int trigPin = 5; // Define the trigPin
const int echoPin = 18; // Define the echoPin

const int maxReadings = 20; // Maximum number of readings to store
long distances[maxReadings]; // Array to store the distances
unsigned long timestamps[maxReadings]; // Array to store the timestamps
int currentIndex = 0; // Index to store the current reading

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB); // Create a WS2812 strip

void setup() { // Setup function
  Serial.begin(115200); // Start the serial communication
  pinMode(trigPin, OUTPUT); // Set the trigPin as an output
  pinMode(echoPin, INPUT); // Set the echoPin as an input

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    while (client.connected()) {
      // Send all stored values to the client
      for (int i = 0; i < maxReadings; i++) { // Iterate over all the values
        if (timestamps[i] != 0) { // Check if the value is valid
          client.print("<b>Timestamp: </b>"); // Send a bold text
          client.print(timestamps[i]); // Send the timestamp
          client.print(" ms - <b> Distance: </b>"); // Send a bold text
          client.print(distances[i]); // Send the distance
          client.print(" cm - <b>Category: </b>"); // Send a bold text
          client.print(categorizeDistance(distances[i])); // Categorize the distance
          client.println("<br>"); // Send a line break
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

String categorizeDistance(long distance) { // Function to categorize the distance
  if (distance < 20) { // If the distance is less than 20 cm
    return "Near"; // Return "Near"
  } else if (distance >= 20 && distance <= 60) { // If the distance is between 20 and 60 cm
    return "Medium"; // Return "Medium"
  } else { // If the distance is greater than 60 cm
    return "Far"; // Return "Far"
  }
}
