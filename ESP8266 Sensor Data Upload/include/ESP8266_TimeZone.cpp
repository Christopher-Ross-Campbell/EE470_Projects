#include "ESP8266_TimeZone.h"

// Define the global string variable
String url = "";

// Function to prompt the user for a choice and set the global variable
void getUserChoice() {
    Serial.println("Please choose one of the following options (1-7):");
    Serial.println("1. Eastern Time Zone (ET) – New York City, NY");
    Serial.println("2. Central Time Zone (CT) –Chicago, IL");
    Serial.println("3. Mountain Time Zone (MT) – Denver, CO");
    Serial.println("4. Pacific Time Zone (PT) – Los Angeles, CA");
    Serial.println("5. Alaska Time Zone (AKT) – Anchorage, AK");
    Serial.println("6. Hawaii-Aleutian Time Zone (HAT) – Honolulu, HI");
    Serial.println("7. Atlantic Time Zone (AT) – San Juan, Puerto Rico");

    while (Serial.available() == 0) {
        // Wait for user input
    }

    int choice = Serial.parseInt();

    switch (choice) {
        case 1:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/New_York";
            break;
        case 2:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Chicago";
            break;
        case 3:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Denver";
            break;
        case 4:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
            break;
        case 5:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Anchorage";
            break;
        case 6:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=Pacific/Honolulu";
            break;
        case 7:
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Puerto_Rico";
            break;
        default:
            Serial.println("Invalid Choice. Assuming Default Value of PT.");
            url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
            return;
    }

    Serial.print("You chose: ");
    Serial.println(url);
}