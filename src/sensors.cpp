#include "sensors.h"

// Define `dht` only in this file
DHT dht(DHTPIN, DHTTYPE);

void setup_sensors() {
    dht.begin();
}

float read_temperature() {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
        return 0.0;
    }
    log_i("Temperature: %.1f", temp);
    return temp;
}
