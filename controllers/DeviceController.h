#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <vector>
#include <string>
#include "../models/SmartDevice.h"

class DeviceController {
    std::vector<SmartDevice*> devices;

public:
    void addDevice(SmartDevice* d) {
        devices.push_back(d);
    }

    void toggleDevice(const std::string& name) {
        for (auto* d : devices) {
            if (d->getName() == name) {
                d->toggle();
                return;
            }
        }
        std::cout << "Device \"" << name << "\" not found!" << std::endl;
    }
};

#endif
