# ESP32 MQTT Node-RED Example

**Author:** Alexandros Panagiotakopoulos  
**Website:** [alexandrospanag.github.io](https://alexandrospanag.github.io)  
**Date:** 28/05/2025

---

## Overview

This project demonstrates how to connect an ESP32 to WiFi and an MQTT broker using the [EspMQTTClient](https://github.com/plapointe6/EspMQTTClient) library.  
It shows how to subscribe and publish to MQTT topics, and is designed for easy integration with [Node-RED](https://nodered.org/) or any MQTT dashboard.

---

## Features

- Connects to WiFi and an MQTT broker
- Subscribes to MQTT topics and prints received messages to the Serial Monitor
- Publishes messages to MQTT topics
- Supports debugging, OTA updates, and web updates

---

## Hardware Requirements

- ESP32 development board
- Micro USB cable
- (Optional) LED on GPIO 2 for further experiments

---

## Getting Started

### 1. **Install Arduino Libraries**

- [EspMQTTClient](https://github.com/plapointe6/EspMQTTClient)

### 2. **Configure WiFi and MQTT**

Edit these lines in your code as needed:

```cpp
EspMQTTClient client(
  "Cudy-Extender",              // WiFi SSID
  "",                           // WiFi password
  "mqttdashboard.com",          // MQTT Broker server (e.g., broker.mqttdashboard.com)
  "",                           // MQTT Username (optional)
  "",                           // MQTT Password (optional)
  "espclientID",                // Unique client ID
  1883                          // MQTT port (default 1883)
);
```

### 3. **Upload the Code**

- Open the `.ino` file in Arduino IDE or VS Code with PlatformIO.
- Select the correct ESP32 board and port.
- Upload the code.

### 4. **Monitor Serial Output**

- Open the Serial Monitor at 115200 baud.
- You should see debug messages and any MQTT messages received.

---

## How the Code Works

- **setup()**: Initializes serial, enables debugging, OTA, and web updates.
- **onConnectionEstablished()**:  
  - Subscribes to `mytopic/test` and `mytopic/wildcardtest/#` topics.
  - Publishes a test message to `mytopic/test`.
  - Publishes a delayed message to `mytopic/wildcardtest/test123`.
- **loop()**: Handles MQTT and WiFi events.

---

## Example Node-RED Flow

You can use Node-RED to send and receive messages to/from your ESP32.  
Example topics:
- `mytopic/test`
- `mytopic/wildcardtest/#`

**To test:**
- Use an MQTT out node to publish to `mytopic/test`.
- Use an MQTT in node to subscribe to `mytopic/test` and see messages from the ESP32.

---

## Advanced Features

- **OTA Updates:** Update your ESP32 firmware over WiFi.
- **Web Updater:** Update via a web interface.
- **Last Will Message:** Notifies if the ESP32 goes offline.

---

## Useful Links

- [EspMQTTClient GitHub](https://github.com/plapointe6/EspMQTTClient)
- [Node-RED](https://nodered.org/)
- [MQTT Explorer](https://mqtt-explorer.com/)
- [Public MQTT Broker List](https://github.com/mqtt/mqtt.github.io/wiki/public_brokers)

---

**Tip:**  
You can expand this project to control LEDs, relays, or sensors via MQTT and Node-RED by adding more subscriptions and publish calls in the code.

---
