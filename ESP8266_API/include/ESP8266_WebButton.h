#ifndef ESP8266_WEBBUTTON_H
#define ESP8266_WEBBUTTON_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Function to make a GET request and return the response as a string
String httpGetButton(String url);

#endif 