#ifndef SENSOR_H
#define SENSOR_H

#include <DHT.h>
#include <Adafruit_Sensor.h>

class Sensor {
public:
    Sensor(uint8_t pin, uint8_t type);
    float getTemperature();
    float getHumidity();
private:
    DHT dht;
};

#endif // SENSOR_H