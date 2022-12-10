DHT11
------------------------------

ATTENTION: PLEASE CHECK YOUR DHT11 SENSOR MODULE! IF IT DOESN'T RESEMBLE THE PICTURE OR HAS MORE THAN 1 PIN YOU NEED TO CHECK THE PIN CONNECTION (some DHT11 sensors have the VCC & GND backwards!!! )! 


The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin (no analog input pins needed).

This description was taken from: https://shop.evilmadscientist.com/productsmenu/716#:~:text=The%20DHT11%20is%20a%20basic,no%20analog%20input%20pins%20needed).



| DHT11 | ESP32 |
| --------------- | --------------- |
| Left Sensor Pin <--- | D4 (PIN 4) |
| VDD/VIN | DIGITAL 3V3 |
| Right Sensor Pin GND ---> | DIGITAL GND|

![](https://circuitdigest.com/sites/default/files/circuitdiagram_mic/ESP32-interfacing-with-dht11.png)



Picture source was taken from: https://circuitdigest.com/sites/default/files/circuitdiagram_mic/ESP32-interfacing-with-dht11.png
