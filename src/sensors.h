#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>

#define DHTPIN 27  // Change to your actual pin
#define DHTTYPE DHT11

// Declare `dht` as `extern` so it is defined only once in `sensors.cpp`
extern DHT dht;

void setup_sensors();
float read_temperature();

#endif  // SENSORS_H
