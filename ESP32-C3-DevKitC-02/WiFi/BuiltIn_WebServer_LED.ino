/*********
 By Alexandros Panagiotakopoulos
*********/

//Connect the LED into D4

#include <WiFi.h> // Load Wi-Fi library
#include "Freenove_WS2812_Lib_for_ESP32.h" //Original Library can be downloaded from here: https://www.arduino.cc/reference/en/libraries/freenove-ws2812-lib-for-esp32/


//Settings for the ESP32-C3 DevKitC-02
#define LEDS_COUNT  1 //define the LED row count
#define LEDS_PIN  8 //define the LED Pins
#define CHANNEL   0 //define the channel


const char* ssid = "<enter your ssid password>"; //Enter your WiFi's ID
const char* password = "<enter your ssid password>"; //Enter your WiFi's PASSWORD

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String outputLEDSTATE = "off";

// Assign output variables to GPIO pins
const int outputLED = 4;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;



Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);


void setup() {
  Serial.begin(9600); //begin the serial baud rate to 9600 bauds
  // Initialize the output variables as outputs
  pinMode(outputLED, OUTPUT);
  // Set outputs to LOW
  digitalWrite(outputLED, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid); //print the ssid into the serial port
  WiFi.begin(ssid, password); //begin establishing the WiFi connection
  while (WiFi.status() != WL_CONNECTED) { //While the WiFi is connected
    delay(500); //delay for approximately half a second
    Serial.print("."); //print a dot into the Serial Port
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  strip.begin(); //begin the LED Strip
  strip.setBrightness(20);  //set the LED Brightness to 20
  server.begin(); //begin the server communication
}

void loop(){
  delay(1000);
  strip.setBrightness(20);  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Green LED On, Orange LED Off"); //print what state the LED is in into the Serial Port
              outputLEDSTATE = "on"; //the Green LED is ON, the Orange is OFF state
              digitalWrite(outputLED, HIGH);
                 for (int i = 0; i < LEDS_COUNT; i++) {
                strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT+50) & 255));
                }
                strip.show();
                delay(1000);
    
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Orange LED On, Green LED Off"); //print what state the LED is in into the Serial Port
              outputLEDSTATE = "off"; //the Orange LED is ON, the Green is OFF state
              digitalWrite(outputLED, LOW);
              delay(1000);
              for (int i = 0; i < LEDS_COUNT; i++) {
              strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT+10) & 255));
              }
              strip.show();
              delay(1000);
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #60c0f0; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #db7a18;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 LED Web Server</h1>");
            
            // If the outputState is off, it displays the ON button       
            if (outputLEDSTATE=="off") {
              client.println("<p>GREEN = ON, ORANGE = OFF </p>");
              client.println("<p><a href=\"/4/on\"><button class=\"button\">GREEN</button></a></p>");
            } else {
              client.println("<p>ORANGE = ON, GREEN = OFF </p>");
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">ORANGE</button></a></p>");
            } 
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
