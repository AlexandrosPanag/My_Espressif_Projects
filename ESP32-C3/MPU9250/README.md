# ESP32-C3 MPU9250 & BMP280 Sensor Example

This project demonstrates how to read data from an **MPU9250** (9-axis IMU: accelerometer, gyroscope, magnetometer) and a **BMP280** (temperature and pressure sensor) using an **ESP32-C3** microcontroller over I2C.

## Features

- Reads and prints:
  - Accelerometer (X, Y, Z, magnitude)
  - Gyroscope (X, Y, Z)
  - Magnetometer (X, Y, Z, horizontal direction)
  - Temperature and pressure from BMP280
- Uses [MPU9250_asukiaaa](https://github.com/asukiaaa/MPU9250_asukiaaa) and [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library) libraries
- Configurable I2C pins for ESP32-C3

## Wiring

| ESP32-C3 Pin | MPU9250 Pin | BMP280 Pin |
|--------------|-------------|------------|
| 3.3V or 5V   | VCC         | VCC        |
| GND          | GND         | GND        |
| GPIO8        | SDA         | SDA        |
| GPIO9        | SCL         | SCL        |

> **Note:**  
> - Default I2C pins for ESP32-C3-DEVKITM-1 are GPIO8 (SDA) and GPIO9 (SCL).  
> - Ensure your sensors are powered with the correct voltage.

## Libraries Required

- [MPU9250_asukiaaa](https://github.com/asukiaaa/MPU9250_asukiaaa)
- [Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)

Install these libraries via the Arduino Library Manager or PlatformIO.


## Example Output

```
accelX: 0.01	accelY: 0.02	accelZ: 0.98	accelSqrt: 0.98	gyroX: 0.01	gyroY: 0.00	gyroZ: 0.00	magX: 123	maxY: 456	magZ: 789	horizontalDirection: 45.67	Temperature(*C): 24.56	Pressure(Pa): 100234.56
```

## Customization

- **I2C Pins:**  
  Change `Wire.begin(8, 9);` in `setup()` if you use different pins.
- **Sensor Addresses:**  
  - MPU9250 default: `0x68` (change to `0x69` if AD0 is high)
  - BMP280 default: `0x76` (change to `0x77` if needed)

---

**Author:** Alexandros Panagiotakopoulos  
[alexandrospanag.github.io](https://alexandrospanag.github.io)
