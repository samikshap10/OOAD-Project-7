#include "SmartDevice.h"

void SmartDevice::notify() {
    for (auto* o : observers)
        o->update(this);
}
