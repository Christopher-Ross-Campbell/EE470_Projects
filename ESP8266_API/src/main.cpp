// Inclusions for header fIles and function files
#include <Arduino.h>
#include "ESP8266_Internet.h"
#include "ESP8266_SendData.h"
#include "ESP8266_WebButton.h"
#include "ESP8266_LED.h"
#include "ESP8266_RGB.h"
#include "ESP8266_RGB_PWM.h"


unsigned long previousMillis = 0;      // Stores last time the LED was updated
const long interval = 30000;           // Interval in milliseconds (20 seconds)

// Define Wi-Fi credentials
const char* ssid = "CRCiPhone";
const char* password = "kgtwc8qlttkr";


#define BUTTON_PIN D3     // GPIO pin where the button is connected
#define RED_PIN D5
#define GREEN_PIN D6
#define BLUE_PIN D7

String url = "https://crcampbell.net/results.txt";
String RGB = "https://crcampbell.net/RGB.txt";
String LED_State;

int r;
int b;
int g;

RGB_LED led(RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {
    // Initialize Serial for debugging
    Serial.begin(9600);
    led.begin();

    // Connect to Wi-Fi
    connectToWiFi(ssid, password);

    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configure button pin as input with pull-up

}

// Main function loops
void loop() {

    unsigned long currentMillis = millis();  // Get the current time

     if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Update the time for the last execution

    LED_State = httpGetButton(url);
    Serial.println(LED_State);
    controlLED(LED_State);
    delay(1000);
    httpGetRGB(RGB, r, g, b);
    led.setColor(r, g, b);

    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
     }
    

    if (digitalRead(BUTTON_PIN) == LOW) {  // Button is pressed, active LOW

        Serial.println("Button pressed! Message Sent to SLACK");
        sendData();
        delay(1000);  // Debounce delay
    }
}