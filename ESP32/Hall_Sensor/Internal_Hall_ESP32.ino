int value = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){

  value = hallRead();

  Serial.println("Hall sensor: "+ String(value));
  delay(1000);
}
