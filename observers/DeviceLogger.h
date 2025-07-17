#ifndef DEVICE_LOGGER_H
#define DEVICE_LOGGER_H

#include "Observer.h"
#include "../models/SmartDevice.h"
#include <iostream>

class DeviceLogger : public Observer {
public:
    void update(SmartDevice* device) override {
        std::cout << "[Logger] " << device->getType()
                  << " \"" << device->getName()
                  << "\" is now " << (device->getState() ? "ON" : "OFF") << std::endl;
    }
};

#endif
