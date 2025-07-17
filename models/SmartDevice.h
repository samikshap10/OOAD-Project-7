#ifndef SMART_DEVICE_H
#define SMART_DEVICE_H

#include <string>
#include <vector>
#include "../observers/Observer.h"

class SmartDevice {
protected:
    std::string name;
    bool isOn;
    std::vector<Observer*> observers;

public:
    SmartDevice(const std::string& deviceName) : name(deviceName), isOn(false) {}
    virtual ~SmartDevice() {}

    virtual void toggle() {
        isOn = !isOn;
        notify();
    }

    virtual std::string getType() const = 0;
    std::string getName() const { return name; }
    bool getState() const { return isOn; }

    void attach(Observer* o) { observers.push_back(o); }
    void notify();
};

#endif
