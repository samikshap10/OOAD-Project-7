#ifndef FAN_H
#define FAN_H

#include "SmartDevice.h"

class Fan : public SmartDevice {
public:
    Fan(const std::string& name) : SmartDevice(name) {}
    std::string getType() const override { return "Fan"; }
};

#endif
