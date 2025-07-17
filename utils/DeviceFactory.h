/**
 * @file DeviceFactory.h
 * @brief Factory class for creating smart devices in SmartHomeSim.
 *
 * The `DeviceFactory` class provides a static method to instantiate smart devices
 * like Lights, Fans, and Thermostats based on a given type string. This decouples
 * device creation logic from the main application and promotes extensibility.
 *
 * Design Pattern:
 * - Factory Pattern: Centralizes object creation logic and returns pointers
 *   to dynamically allocated `SmartDevice` instances based on string input.
 *
 * Usage:
 * SmartDevice* device = DeviceFactory::createDevice("Fan", "Bedroom Fan");
 */

#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "../models/Light.h"
#include "../models/Fan.h"
#include "../models/Thermostat.h"

class DeviceFactory {
public:
    /**
     * @brief Creates a smart device of the specified type and name.
     * 
     * Supported types: "Light", "Fan", "Thermostat"
     *
     * @param type The type of device to create (case-sensitive)
     * @param name The name to assign to the new device
     * @return Pointer to the newly created SmartDevice, or nullptr if type is invalid
     */
    static SmartDevice* createDevice(const std::string& type, const std::string& name) {
        if (type == "Light") return new Light(name);
        if (type == "Fan") return new Fan(name);
        if (type == "Thermostat") return new Thermostat(name);
        return nullptr; // Unknown device type
    }
};

#endif // DEVICE_FACTORY_H
