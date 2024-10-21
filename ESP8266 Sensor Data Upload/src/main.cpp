// Inclusions for header fIles and function files
#include <Arduino.h>
#include "ESP8266_Internet.h"
#include "ESP8266_Internet.cpp"
#include "ESP8266_Sensor.h"
#include "ESP8266_Sensor.cpp"
#include "ESP8266_DateTime.h"
#include "ESP8266_DateTime.cpp"
#include "ESP8266_TimeZone.h"
#include "ESP8266_TimeZone.cpp"
#include "ESP8266_SendData.h"
#include "ESP8266_SendData.cpp"

// Define Wi-Fi credentials
const char* ssid = "CRCiPhone";
const char* password = "kgtwc8qlttkr";



#define DHT_PIN D5        // GPIO pin where the DHT11 is connected
#define DHT_TYPE DHT11    // Define Sensor Type (DHT11)
#define BUTTON_PIN D3     // GPIO pin where the button is connected

Sensor sensor(DHT_PIN, DHT_TYPE);  // Initialize the sensor object

void setup() {
    // Initialize Serial for debugging
    Serial.begin(9600);

    // Connect to Wi-Fi
    connectToWiFi(ssid, password);

    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Configure button pin as input with pull-up
    getUserChoice(); // Call function to get user input on timezone selection

    // Promt user to press button
    Serial.println("Press the button to get temperature and humidity data...");


}

// Main function loops
void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {  // Button is pressed, active LOW

        // Get sensor readings (needs DHT Libraries)
        float temperature = sensor.getTemperature();
        float humidity = sensor.getHumidity();

        Serial.println("Button pressed! Sending GET request...");

        // Send GET request and get the response
        String dateTime = httpGetDateTime(url); //Function call to get time stamp

        // Function call to send data to database
        sendData(temperature, humidity, dateTime);

        // Print the response to the serial monitor
        Serial.println("DateTime response: ");
        Serial.println(dateTime);

        // Debounce/wait to prevent multiple calls
        while (digitalRead(BUTTON_PIN) == LOW) {
            delay(10);
        }

        // Check if sensor is working (if either NaN, faulty)
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
        } else {
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.println("°C");
            
            Serial.print("Humidity: ");
            Serial.print(humidity);
            Serial.println("%");
        }
        
        delay(1000);  // Debounce delay
    }
}