/**
 * @file DeviceController.h
 * @brief Manages smart devices in the SmartHomeSim system.
 *
 * The `DeviceController` class serves as the central controller for managing
 * a collection of smart devices. It provides methods to add devices, toggle
 * them by name, and list all registered devices with their current state.
 *
 * Responsibilities:
 * - Maintain a registry of active devices
 * - Provide interface to toggle device states by name
 * - Display a list of current devices and their statuses
 *
 */

#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <vector>
#include <string>
#include <iostream>
#include "../models/SmartDevice.h"

class DeviceController {
    std::vector<SmartDevice*> devices;  ///< Collection of all registered smart devices

public:
    /**
     * @brief Adds a new device to the system.
     * @param d Pointer to a SmartDevice instance
     */
    void addDevice(SmartDevice* d) {
        devices.push_back(d);
    }

    /**
     * @brief Toggles the state of a device by name.
     * 
     * Searches through the list of registered devices and toggles the one 
     * that matches the given name. If not found, an error message is shown.
     * 
     * @param name The name of the device to toggle
     */
    void toggleDevice(const std::string& name) {
        for (auto* d : devices) {
            if (d->getName() == name) {
                d->toggle();
                return;
            }
        }
        std::cout << "Device \"" << name << "\" not found!" << std::endl;
    }

    /**
     * @brief Lists all registered smart devices and their current states.
     */
    void listDevices() const {
        if (devices.empty()) {
            std::cout << "[System] No devices currently registered.\n";
            return;
        }

        std::cout << "\n=== Registered Smart Devices ===\n";
        for (const auto* device : devices) {
            std::cout << "- " << device->getType() << ": " << device->getName()
                      << " [State: " << (device->getState() ? "ON" : "OFF") << "]\n";
        }
        std::cout << "=================================\n";
    }

    std::vector<SmartDevice*>& getAllDevices() {
    return devices;
}

};

#endif // DEVICE_CONTROLLER_H
