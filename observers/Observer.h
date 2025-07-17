#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class SmartDevice;

class Observer {
public:
    virtual void update(SmartDevice* device) = 0;
    virtual ~Observer() {}
};

#endif
