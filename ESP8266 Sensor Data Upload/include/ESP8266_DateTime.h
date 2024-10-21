#ifndef ESP8266_DATETIME_H
#define ESP8266_DATETIME_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Function to make a GET request and return the response as a string
String httpGetDateTime(const char* url);

#endif 