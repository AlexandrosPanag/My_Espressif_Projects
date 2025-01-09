/*********
 By the Autonomous Systems Laboratory 2022-2023, for the Department of Informatics & Telecommunications
 Lesson "Internet of Things" Computer System Courses Flow of the 7th Semester
*********/

void setup(){ //set-up point here the code runs only once
  Serial.begin(9600); //Initialize the serial baud rate to 9600 bauds
}

void loop(){ //eternal loop point; this code will run again and again
  Serial.println("Hello World"); //print hello world
  delay(1000); //delay approximately 1 second
}