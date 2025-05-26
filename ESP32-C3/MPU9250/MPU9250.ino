// Arduino code to read data from MPU9250 and BMP280 sensors using I2C communication
// Code written by Alexandros Panagiotakopoulos - alexandrospanag.github.io
// DATE: 27/05/2000

#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C address 0x76 for BMP280, change to 0x77 if needed
MPU9250_asukiaaa mpu; // I2C address 0x68 for MPU9250, change to 0x69 if needed
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection; 
uint16_t mX, mY, mZ; 


void setup() {
  Serial.begin(115200); 
  Wire.begin(8, 9); // Change to your SDA and SCL pins if necessary
  mpu.setWire(&Wire); // Set the Wire instance to use for MPU9250 communication
  bmp.begin(); // Initialize BMP280, default I2C address is 0x76
  mpu.beginAccel(); // Initialize accelerometer
  mpu.beginGyro(); // Initialize gyroscope
  mpu.beginMag(); // Initialize magnetometer
}

void loop() { 
  if (mpu.accelUpdate() == 0) { 
    aX = mpu.accelX(); // Get accelerometer data
    aY = mpu.accelY(); // Get accelerometer data
    aZ = mpu.accelZ(); // Get accelerometer data
    aSqrt = mpu.accelSqrt(); // Calculate the square root of the sum of squares of accelerometer data
    Serial.print("accelX: " + String(aX)); // Print accelerometer data
    Serial.print("\taccelY: " + String(aY)); // Print accelerometer data
    Serial.print("\taccelZ: " + String(aZ)); // Print accelerometer data
    Serial.print("\taccelSqrt: " + String(aSqrt)); // Print the square root of the sum of squares of accelerometer data
  }
  if (mpu.gyroUpdate() == 0) { // Check if gyroscope data is updated
    gX = mpu.gyroX(); // Get gyroscope data
    gY = mpu.gyroY(); // Get gyroscope data
    gZ = mpu.gyroZ(); // Get gyroscope data
    Serial.print("\tgyroX: " + String(gX)); // Print gyroscope data
    Serial.print("\tgyroY: " + String(gY)); // Print gyroscope data
    Serial.print("\tgyroZ: " + String(gZ)); // Print gyroscope data
  }

  if (mpu.magUpdate() == 0) { // Check if magnetometer data is updated
    mX = mpu.magX(); // Get magnetometer data
    mY = mpu.magY(); // Get magnetometer data
    mZ = mpu.magZ(); // Get magnetometer data
    mDirection = mpu.magHorizDirection(); // Calculate horizontal direction from magnetometer data
    Serial.print("\tmagX: " + String(mX)); // Print magnetometer data
    Serial.print("\tmaxY: " + String(mY)); // Print magnetometer data
    Serial.print("\tmagZ: " + String(mZ)); // Print magnetometer data
    Serial.print("\thorizontalDirection: " + String(mDirection)); // Print horizontal direction from magnetometer data
  }

  Serial.print("\tTemperature(*C): "); // Print temperature from BMP280
  Serial.print(bmp.readTemperature()); // Read temperature from BMP280

  Serial.print("\tPressure(Pa): "); // Print pressure from BMP280W
  Serial.print(bmp.readPressure()); // Read pressure from BMP280

  Serial.println(""); // Print a new line for better readability
  delay(3000); // Delay for 3 seconds before the next loop iteration
  }