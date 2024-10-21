#ifndef MY_HTTP_CLIENT_H
#define MY_HTTP_CLIENT_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Function to make a GET request and return the response as a string
String httpGetDateTime(const char* url);

#endif // MY_HTTP_CLIENT_H