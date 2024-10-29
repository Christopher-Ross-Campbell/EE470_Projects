#include "ESP8266_WebButton.h"
#include <ArduinoJson.h>

String httpGetButton(String url) {
    WiFiClientSecure client;
    client.setInsecure();  // Disable SSL certificate verification
    HTTPClient http;

    Serial.println("Requesting: --> " + String(url));
    Serial.println();
    
    if (http.begin(client, url)) {
        int httpCode = http.GET();  // Send GET request
        Serial.println("Response Code <--: " + String(httpCode));
        
        if (httpCode > 0) {
            // Check if the response code is HTTP_OK (200)
            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();  // Get response payload
                http.end(); // Close connection

                return payload;  // Return the parsed/modified string
            }
        } else {
            Serial.println("GET request failed, error: " + http.errorToString(httpCode));
        }
        http.end();  // Close connection
    } else {
        Serial.println("[HTTPS] Unable to Connect");
    }

    return String();  // Return empty string if request failed
}