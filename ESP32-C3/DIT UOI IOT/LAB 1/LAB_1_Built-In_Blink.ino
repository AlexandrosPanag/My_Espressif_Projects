/*********
 By the Autonomous Systems Laboratory 2022-2023, for the Department of Informatics & Telecommunications
 Lesson "Internet of Things" Computer System Courses Flow of the 7th Semester
*********/

//Original Library can be downloaded from here: https://www.arduino.cc/reference/en/libraries/freenove-ws2812-lib-for-esp32/
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  1
#define LEDS_PIN  8
#define CHANNEL   0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
  strip.begin();
  strip.setBrightness(20);  
}

void loop() {
  delay(1000);
  strip.setBrightness(20);  
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  }  
  delay(1000);
  strip.setBrightness(0);  
}