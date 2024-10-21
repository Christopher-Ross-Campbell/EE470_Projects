#include "ESP8266_Internet.h"

// Function to connect to Wi-Fi
void connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n\rConnected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    String macAddress = WiFi.macAddress();

    // Print the MAC address to the serial monitor
    Serial.print("ESP8266 MAC Address: ");
    Serial.println(macAddress);
}

