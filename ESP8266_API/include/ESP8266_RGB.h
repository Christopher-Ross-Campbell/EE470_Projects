#ifndef ESP8266_RGB_H
#define ESP8266_RGB_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Function to make a GET request and return the response as a string
bool httpGetRGB(String RGB, int &r, int &g, int &b);

#endif 