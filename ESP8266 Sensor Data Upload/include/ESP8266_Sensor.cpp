#include "ESP8266_Sensor.h"

Sensor::Sensor(uint8_t pin, uint8_t type) : dht(pin, type) {
    dht.begin();
}

float Sensor::getTemperature() {
    return dht.readTemperature();
}

float Sensor::getHumidity() {
    return dht.readHumidity();
}