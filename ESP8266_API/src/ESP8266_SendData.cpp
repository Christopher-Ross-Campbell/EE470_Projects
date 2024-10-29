#include "ESP8266_SendData.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void sendData() {
    if (WiFi.status() == WL_CONNECTED) {
        
        WiFiClientSecure client;
        client.setInsecure();  // Disable SSL certificate verification
        HTTPClient http;
        String serverPath = "https://maker.ifttt.com/trigger/button_pressed/json/with/key/q1T1NWBGXSG2dc0NluWsm"; 

        // Construct the URL 
        String POST_URL = serverPath;

        // Initialize HTTP
        http.begin(client, POST_URL);  
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        // Send the POST request
        int httpResponseCode = http.POST("");

        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        // Close connection
        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}