#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
#include "strategies/TemperatureStrategy.h"

class Thermostat : public SmartDevice {
    TemperatureStrategy* strategy = nullptr;

public:
    Thermostat(const std::string& name) : SmartDevice(name) {}

    void applyTemperatureStrategy() {
    if (strategy) strategy->apply(); 
    }
    std::string getType() const override { return "Thermostat"; }

    void setStrategy(TemperatureStrategy* s) { strategy = s; }

    void toggle() override {
        SmartDevice::toggle();
        if (strategy && getState()) strategy->apply();
    }
};

#endif
