#include "ESP8266_RGB_PWM.h"

RGB_LED::RGB_LED(int redPin, int greenPin, int bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin) {}

void RGB_LED::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void RGB_LED::setColor(int red, int green, int blue) {
    analogWrite(_redPin, red);
    analogWrite(_greenPin, green);
    analogWrite(_bluePin, blue);
}