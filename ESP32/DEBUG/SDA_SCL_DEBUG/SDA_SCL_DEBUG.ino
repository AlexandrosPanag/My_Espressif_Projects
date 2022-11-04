/*
 This code was written  Alexandros Panagiotakopoulos
*********/

//Find the default SPI pins for your board
//Make sure you have the right board selected in Tools > Boards
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println("********************************");
  //print your SDA pin
  Serial.println("SDA:");
  Serial.print(SDA);
  Serial.println();
  //print your SCL pin
  Serial.println("SCL: ");
  Serial.print(SCL);  
  Serial.println();
  delay(1000);
}
