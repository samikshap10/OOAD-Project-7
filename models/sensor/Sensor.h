#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <iostream>
#include "models/SmartDevice.h"
#include "models/Thermostat.h"
#include "strategies/TemperatureStrategy.h"

class Sensor {
    std::vector<SmartDevice*> subscribers;

public:
    void subscribe(SmartDevice* device) {
        subscribers.push_back(device);
    }

    void trigger() {
        std::cout << "[Sensor] Environmental change triggered!\n";
        for (auto* device : subscribers) {
            // Optionally: check type before reacting
            Thermostat* t = dynamic_cast<Thermostat*>(device);
            if (t) {
                std::cout << "Notifying " << t->getName() << "...\n";
                t->applyTemperatureStrategy();  // new method
            }
        }
    }
};

#endif
