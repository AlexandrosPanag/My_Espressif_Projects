// By Alexandros Panagiotakopoulos
// January 05/01/2025

// For the digital pin reference please refer to the link bellow:
//https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT); //connect to D2 
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(4, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);                      // wait for a second
  digitalWrite(4, LOW);  // turn the LED on (HIGH is the voltage level)\
  //digitalWrite(LED_BUILTIN, LOW);
  delay(1000);                      // wait for a second
}
