#ifndef ECO_MODE_H
#define ECO_MODE_H

#include "TemperatureStrategy.h"
#include <iostream>

class EcoMode : public TemperatureStrategy {
public:
    void apply() override {
        std::cout << "[Thermostat] Eco Mode: Set to 68°F for energy saving.\n";
    }
};

#endif
