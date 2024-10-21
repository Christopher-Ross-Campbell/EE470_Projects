#ifndef DATASENDER_H
#define DATASENDER_H

#include <Arduino.h>

void sendData(float temperature, float humidity, String dateTime);

#endif // DATASENDER_H