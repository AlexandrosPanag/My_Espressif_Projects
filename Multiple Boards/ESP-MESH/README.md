ESP-MESH
-----

| Compiler/IDE | Download Link |
| --------------- | ---------------- |
| VSCode with PlatformIO | [Download Link](https://platformio.org/install/ide?install=vscode) |


This code was compiled on Visual Studio Along with the PlatformIO extension.

This project illustrates how an ESP32 Board, an ESP32C3 Board along with an ESP8266 Board can exchange data and establish a Wi-Fi Mesh connection.

Add to your platform.ini the following lines:

monitor_speed = 9600
lib_deps = painlessmesh/painlessMesh @ ^1.4.5
    ArduinoJson
    arduinoUnity
    TaskScheduler
    AsyncTCP
