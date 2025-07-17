#ifndef LIGHT_H
#define LIGHT_H

#include "SmartDevice.h"

class Light : public SmartDevice {
public:
    Light(const std::string& name) : SmartDevice(name) {}
    std::string getType() const override { return "Light"; }
};

#endif
