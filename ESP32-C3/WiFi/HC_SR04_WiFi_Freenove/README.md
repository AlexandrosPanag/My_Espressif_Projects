#HC_SR04 WiFi Freenove

#Overview

This project is designed to run on an ESP32C3 microcontroller. It handles client connections, sends stored sensor readings to the client, and categorizes distances into different categories based on predefined thresholds.

Author
Name: Alexandros Panagiotakopoulos
Website: alexandrospanag.github.io
Date: January 2025
Libraries
WiFi: For connecting to WiFi networks.
WiFiClient: For handling client connections.
Freenove_WS2812_Lib_for_ESP32: For controlling WS2812 LEDs.
Pin Definitions
LEDS_COUNT: Number of LEDs.
LEDS_PIN: Pin connected to the LEDs.
CHANNEL: Channel for the LEDs.
trigPin: Pin connected to the trigger of the ultrasonic sensor.
echoPin: Pin connected to the echo of the ultrasonic sensor.
Constants
ssid: SSID of the WiFi network.
password: Password of the WiFi network.
maxReadings: Maximum number of sensor readings to store.
Variables
distances: Array to store the distance readings.
timestamps: Array to store the timestamps of the readings.
currentIndex: Index to store the current reading.
server: WiFi server running on port 80.
strip: WS2812 LED strip object.
Functions
void setup()
The setup function initializes the serial communication, sets up the pin modes, and connects to the WiFi network.

void loop()
The loop function continuously checks for client connections and sends stored sensor readings to the connected client. It also categorizes the distances and sends the categorized data.

Key Operations:

Iterates over stored sensor readings.
Sends timestamp, distance, and categorized distance to the client.
Waits for 1 second before sending the next set of data.
Closes the client connection and prints a message when the client disconnects.
String categorizeDistance(long distance)
The categorizeDistance function categorizes a given distance into one of three categories: "Near", "Medium", or "Far".

Parameters:

distance (long): The distance value to be categorized.
Returns:

String: The category of the distance ("Near", "Medium", or "Far").
Example Code
Usage
Client Connection: The ESP32C3 waits for a client to connect. Once connected, it sends the stored sensor readings to the client.
Data Transmission: The sensor readings include a timestamp, distance, and categorized distance. The data is sent every second.
Categorization: The distances are categorized into "Near", "Medium", or "Far" based on predefined thresholds.
Disconnection: The client connection is closed after the data is sent, and a message is printed to the serial monitor.
Example Output
This documentation provides an overview of the code's functionality, key operations, and usage. It helps in understanding how the ESP32C3 handles client connections, sends sensor data, and categorizes distances.
