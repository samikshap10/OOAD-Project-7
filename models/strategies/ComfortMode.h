#ifndef COMFORT_MODE_H
#define COMFORT_MODE_H

#include "TemperatureStrategy.h"
#include <iostream>

class ComfortMode : public TemperatureStrategy {
public:
    void apply() override {
        std::cout << "[Thermostat] Comfort Mode: Set to 72°F for comfort.\n";
    }
};

#endif
