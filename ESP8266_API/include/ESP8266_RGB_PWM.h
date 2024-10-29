#ifndef ESP8266_RGB_PWM_H
#define ESP8266_RGB_PWM_H

#include <Arduino.h>

class RGB_LED {
public:
    RGB_LED(int redPin, int greenPin, int bluePin);
    void begin();
    void setColor(int red, int green, int blue);

private:
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif