
ESP8266 Project Documentation
Overview
This project is designed to run on an ESP8266 microcontroller. It reads temperature and humidity data from a DHT11 sensor, handles client connections, and sends the sensor readings to the client.

Author
Name: Alexandros Panagiotakopoulos
Website: alexandrospanag.github.io
Date: January 2025
License
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

Libraries
DHT: For reading data from the DHT11 sensor.
WiFi: For connecting to WiFi networks.
WiFiClient: For handling client connections.
Pin Definitions
DHTPIN: Pin connected to the DHT11 sensor (GPIO2).
DHTTYPE: Type of DHT sensor (DHT11).
LED_BUILTIN: Onboard LED pin.
Pin 4: Connected to D2.
Pin 0: Connected to D3.
Constants
ssid: SSID of the WiFi network.
password: Password of the WiFi network.
maxReadings: Maximum number of sensor readings to store.
Variables
temperatures: Array to store the temperature readings.
timestamps: Array to store the timestamps of the readings.
currentIndex: Index to store the current reading.
server: WiFi server running on port 80.
dht: DHT sensor object.
Functions
void setup()
The setup function initializes the serial communication, sets up the pin modes, starts the DHT sensor, and connects to the WiFi network.

void loop()
The loop function continuously reads temperature and humidity data from the DHT11 sensor, stores the readings, and handles client connections to send the sensor data.

Key Operations:

Reads temperature and humidity data from the DHT11 sensor.
Checks for failed sensor readings and handles errors.
Computes the heat index in both Fahrenheit and Celsius.
Stores the current temperature and timestamp in arrays.
Handles client connections and sends the stored sensor data.
float readTemperature()
The readTemperature function reads the temperature from the DHT11 sensor and returns it.

float readHumidity()
The readHumidity function reads the humidity from the DHT11 sensor and returns it.

float computeHeatIndex(float temperature, float humidity, bool isFahrenheit)
The computeHeatIndex function computes the heat index based on the temperature and humidity readings.

Example Code
Usage
Client Connection: The ESP8266 waits for a client to connect. Once connected, it sends the stored sensor readings to the client.
Data Transmission: The sensor readings include a timestamp and temperature. The data is sent every second.
Error Handling: If the sensor readings fail, an error message is printed, and the LEDs are turned off.
Heat Index Calculation: The heat index is computed in both Fahrenheit and Celsius.
Temperature Check: The temperature is checked, and appropriate messages are printed. LEDs are turned on or off based on the temperature.
Example Output
By following these steps, you can add the provided documentation to your GitHub repository.
