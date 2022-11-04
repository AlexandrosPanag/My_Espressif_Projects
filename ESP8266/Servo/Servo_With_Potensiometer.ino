/*
 * Created by Alexandros Panagiotakopoulos
*/

#include <Servo.h>

Servo servo_1; // servo controller (multiple can exist)

int servo_pin = 4; // PWM pin for servo control
int pos = 0;    // servo starting position

void setup() {
  servo_1.attach(servo_pin); // start servo control
}

void loop() {
  int potensiometer_position = analogRead(A0); //read the digital values of the potensiometer 
  
  int positioning = map(potensiometer_position, 0, 1023, 0 , 180); //turn the digital values into degrees

  servo_1.write(positioning); //set the servo in the proper position
  delay(15); //delay 15msec
}
