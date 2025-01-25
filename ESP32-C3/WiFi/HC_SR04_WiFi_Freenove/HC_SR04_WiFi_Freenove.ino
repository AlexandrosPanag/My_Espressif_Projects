// By Alexandros Panagiotakopoulos
// alexandrospanag.github.io
// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

// Date: January 2025

#include <WiFi.h> // Include the WiFi library
#include <WiFiClient.h> // Include the WiFiClient library
#include "Freenove_WS2812_Lib_for_ESP32.h" // Include the WS2812 library

// Freenove Pin Definitions
#define LEDS_COUNT  1
#define LEDS_PIN    8
#define CHANNEL     0

const char *ssid = "mywifiroutername"; // SSID of the network
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
  Serial.print("Connecting to "); // Print a message
  Serial.println(ssid); // Print the SSID

  WiFi.begin(ssid, password); // Connect to the network

  while (WiFi.status() != WL_CONNECTED) { // Wait for the connection
    delay(100); // Wait for the connection
    strip.begin(); // Initialize the strip
    strip.setBrightness(20); // Set the brightness 
  }

  Serial.println(""); // Print a blank line
  Serial.println("WiFi connected."); // Print a message
  Serial.println("IP address: "); // Print the IP address
  Serial.println(WiFi.localIP()); // Print the IP address

  server.begin(); // Start the server
}

void loop() {
  long duration, distance; // Variables to store the duration and distance
  unsigned long currentTimestamp = millis(); // Get the current timestamp
  
  // Clear the trigPin
  digitalWrite(trigPin, LOW); // Set the trigPin LOW
  delayMicroseconds(2); // Wait for 2 microseconds
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH); // Set the trigPin HIGH
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(trigPin, LOW); // Set the trigPin LOW
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH); // Measure the time it takes for the sound wave to return
  
  // Check if the sensor is connected
  if (duration == 0 || duration > 30000) { // If the duration is 0 or greater than 30,000 microseconds
    Serial.println("Sensor not connected or out of range"); // Print a message
  } else {
    // Calculate the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    
    // Store the current values in the arrays
    distances[currentIndex] = distance; // Store the distance
    timestamps[currentIndex] = currentTimestamp; // Store the timestamp
    currentIndex = (currentIndex + 1) % maxReadings; // Circular buffer
    
    // Print the distance and its timestamp
    Serial.print("Timestamp: "); // Print the timestamp
    Serial.print(currentTimestamp); // Print the timestamp
    Serial.print(" ms - Distance: "); // Print the distance in cm
    Serial.print(distance); // Print the distance in cm
    Serial.println(" cm"); // Print the distance in cm

    // Categorize the distance and control the LEDs
    String category = categorizeDistance(distance);
    Serial.print("Category: "); // Print the category
    Serial.println(category); // Print the category
    if (category == "Near") { // If the category is "Near"
      for (int i = 0; i < LEDS_COUNT; i++) { // Iterate over all the LEDs
        strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + 50) & 255)); // Set the color of the LED
      }
    } else if (category == "Medium") { // If the category is "Medium"
      for (int i = 0; i < LEDS_COUNT; i++) { // Iterate over all the LEDs
        strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT) & 255)); // Set the color of the LED
      }
    } else { // If the category is "Far"
      for (int i = 0; i < LEDS_COUNT; i++) { // Iterate over all the LEDs
        strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + 25) & 255)); // Set the color of the LED
      }
    }
    strip.show(); // Show the LEDs
  }
  
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
  } else if (distance >= 20 && distance <= 60) { // If the distance is between 20 and 50 cm
    return "Medium"; // Return "Medium"
  } else { // If the distance is greater than 60 cm
    return "Far"; // Return "Far"
  }
}