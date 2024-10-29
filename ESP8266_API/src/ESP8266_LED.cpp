#include <Arduino.h>
#include "ESP8266_LED.h"

const int LED_PIN = D4;  


void controlLED(String LED_State) {
    pinMode(LED_PIN, OUTPUT);

    if (LED_State == "ON") {
        digitalWrite(LED_PIN, HIGH);  // Turn LED on
        Serial.println("LED is ON");
    } else if (LED_State == "OFF") {
        digitalWrite(LED_PIN, LOW);   // Turn LED off
        Serial.println("LED is OFF");
    }
}