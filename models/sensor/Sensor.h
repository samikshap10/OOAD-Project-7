/**
 * @file Sensor.h
 * @brief Simulated environmental sensor that notifies smart devices of changes.
 *
 * The `Sensor` class models an environmental sensor (e.g., temperature, humidity) that can notify
 * subscribed smart devices of environmental changes. Devices implement `onSensorTriggered(int)` 
 * to define how they react when the sensor triggers a new value.
 *
 * This class supports:
 * - Publishing simulated sensor values
 * - Subscribing smart devices that observe these values
 *
 * Design Patterns:
 * - Implements a basic version of the Publisher/Subscriber model (Observer Pattern)
 *
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <iostream>
#include "models/SmartDevice.h"
#include "models/Thermostat.h"
#include "strategies/TemperatureStrategy.h"

class Sensor {
    std::vector<SmartDevice*> subscribers; ///< List of subscribed smart devices

public:
    /**
     * @brief Subscribes a smart device to receive sensor updates.
     * @param device Pointer to a SmartDevice that should be notified of sensor changes
     */
    void subscribe(SmartDevice* device) {
        subscribers.push_back(device);
    }

    /**
     * @brief Triggers a new sensor value and notifies all subscribed devices.
     * 
     * Each device's `onSensorTriggered(int)` function will be called.
     * Devices can then choose how to react based on the new sensor value.
     *
     * @param newValue The new sensor value (e.g., temperature reading)
     */
    void trigger(int newValue) {
        std::cout << "[Sensor] Environmental change triggered! New value = " << newValue << "\n";

        for (auto* device : subscribers) {
            std::cout << "Notifying " << device->getName() << "...\n";
            device->onSensorTriggered(newValue);  
        }
    }
};

#endif // SENSOR_H
