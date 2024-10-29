#include "ESP8266_RGB.h"
#include <ArduinoJson.h>

bool httpGetRGB(String RGB, int &r, int &g, int &b) {
    WiFiClientSecure client;
    client.setInsecure();  // Disable SSL certificate verification
    HTTPClient http;

    Serial.println("Requesting: --> " + String(RGB));
    Serial.println();
    
    if (http.begin(client, RGB)) {
        int httpCode = http.GET();  // Send GET request
        Serial.println("Response Code <--: " + String(httpCode));
        
        if (httpCode > 0) {
            // Check if the response code is HTTP_OK (200)
            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();  // Get response payload
                http.end(); // Close connection

                // Parse the payload
                int firstComma = payload.indexOf(',');
                int secondComma = payload.indexOf(',', firstComma + 1);
                
                if (firstComma > 0 && secondComma > firstComma) {
                    r = payload.substring(0, firstComma).toInt();
                    g = payload.substring(firstComma + 1, secondComma).toInt();
                    b = payload.substring(secondComma + 1).toInt();
                    return true;  // Indicate success
                }
            }
        } else {
            Serial.println("GET request failed, error: " + http.errorToString(httpCode));
        }
        http.end();  // Close connection
    } else {
        Serial.println("[HTTPS] Unable to Connect");
    }

    return false;  // Indicate failure
}