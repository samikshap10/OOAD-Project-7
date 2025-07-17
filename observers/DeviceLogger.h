/**
 * @file DeviceLogger.h
 * @brief Observer class that logs smart device state changes in SmartHomeSim.
 *
 * The `DeviceLogger` class implements the Observer interface and is used to monitor
 * the state of smart devices. When devices are toggled on or off, this logger receives
 * notifications and outputs them to both the console and an internal log list.
 *
 * This class supports:
 * - Console logging of state changes
 * - Viewing all logged actions via a CLI command
 *
 * Design Pattern:
 * - Observer Pattern: This class observes `SmartDevice` instances for state changes.
 */

#ifndef DEVICE_LOGGER_H
#define DEVICE_LOGGER_H

#include "Observer.h"
#include "../models/SmartDevice.h"
#include <iostream>
#include <vector>
#include <string>

class DeviceLogger : public Observer {
private:
    std::vector<std::string> logs;  ///< Stores string logs of device activity

public:
    /**
     * @brief Called when an observed device's state changes.
     * Logs the new state both to the console and to the internal log list.
     *
     * @param device Pointer to the smart device that triggered the update
     */
    void update(SmartDevice* device) override {
        std::string logEntry = "[Logger] " + device->getType() + " \"" +
                               device->getName() + "\" is now " +
                               (device->getState() ? "ON" : "OFF") + "\n";

        std::cout << logEntry;
        logs.push_back(logEntry);  // Store for later review
    }

    /**
     * @brief Prints all stored logs to the console.
     * Called by the "logs" command in the CLI.
     */
    void printLogs() const {
        if (logs.empty()) {
            std::cout << "[Logger] No actions logged yet.\n";
            return;
        }

        std::cout << "\n===== Device Activity Log =====\n";
        for (const auto& entry : logs) {
            std::cout << entry;
        }
        std::cout << "================================\n";
    }
};

#endif // DEVICE_LOGGER_H
