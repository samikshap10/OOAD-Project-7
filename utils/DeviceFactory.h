#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "../models/Light.h"
#include "../models/Fan.h"
#include "../models/Thermostat.h"

class DeviceFactory {
public:
    static SmartDevice* createDevice(const std::string& type, const std::string& name) {
        if (type == "Light") return new Light(name);
        if (type == "Fan") return new Fan(name);
        if (type == "Thermostat") return new Thermostat(name);
        return nullptr;
    }
};

#endif
