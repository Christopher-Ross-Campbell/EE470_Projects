#include "ESP8266_DateTime.h"
#include <ArduinoJson.h>

String httpGetDateTime(String url) {
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
                //Serial.println("Response: " + payload);
                http.end();

                StaticJsonDocument<200> doc;
                DeserializationError error = deserializeJson(doc, payload);
                String dateTimeParse = doc["dateTime"];
                dateTimeParse = dateTimeParse.substring(0,dateTimeParse.indexOf('.'));
                dateTimeParse.replace("T","%20");
                return dateTimeParse;  // Return the response string
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