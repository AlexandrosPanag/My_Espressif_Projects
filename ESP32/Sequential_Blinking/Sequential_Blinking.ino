/*********
 Edited By Alexandros Panagiotakopoulos
*********/
/*
 * Sequential blinking example (using a breadboard)
*/
#define BLUE_LED 18 //declare GPIO 18 as Blue Led
#define RED_LED 19 // declare GPIO 19 as Red Led
#define GREEN_LED 2 // declare GPIO 2 as Green Led

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(BLUE_LED, OUTPUT); // declare the Blue led as an output
  pinMode(RED_LED, OUTPUT); // declare the Red Led as an output
  pinMode(GREEN_LED, OUTPUT); // declare the Green Led as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(18, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(18, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(19, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(19, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);      
}
