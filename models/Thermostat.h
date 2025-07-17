/**
 * @file Thermostat.h
 * @brief Concrete smart device class representing a Thermostat in SmartHomeSim.
 *
 * The Thermostat class extends SmartDevice and uses the Strategy Pattern to apply
 * dynamic behavior based on sensor input (e.g., temperature changes). It switches
 * between different temperature strategies like EcoMode and ComfortMode.
 *
 * Design Patterns:
 * - Inherits from SmartDevice (base interface for smart devices)
 * - Implements the Strategy Pattern using TemperatureStrategy interface
 * - Uses Observer Pattern to respond to sensor value changes
 *
 * Key Features:
 * - Dynamically switches behavior strategy based on sensor input
 * - Applies selected strategy only when the device is toggled on
 * - Overrides toggle and getType methods for device-specific logic
 */

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
#include "strategies/TemperatureStrategy.h"
#include "strategies/EcoMode.h"
#include "strategies/ComfortMode.h"

class Thermostat : public SmartDevice {
    TemperatureStrategy* strategy = nullptr;  ///< Pointer to current strategy instance

public:
    /**
     * @brief Constructs a Thermostat with the given name.
     * @param name The name of the thermostat device
     */
    Thermostat(const std::string& name) : SmartDevice(name) {}

    /**
     * @brief Reacts to sensor input (e.g., temperature) by switching strategy.
     * 
     * If temperature exceeds 28, it switches to ComfortMode.
     * Otherwise, it stays or switches to EcoMode.
     * Previous strategy is deleted to prevent memory leaks.
     * 
     * @param value The sensor value (e.g., temperature reading)
     */
    void onSensorTriggered(int value) override {
        std::cout << "[Thermostat] " << getName() << " responding to sensor change...\n";

        // Dynamically select strategy based on temperature threshold
        delete strategy; // Prevent memory leak by deleting current strategy

        if (value > 28) {
            std::cout << "  Switching to Comfort Mode.\n";
            strategy = new ComfortMode();
        } else {
            std::cout << "  Staying in Eco Mode.\n";
            strategy = new EcoMode();
        }

        // Strategy can be applied immediately or deferred based on state
        // applyTemperatureStrategy();
    }

    /**
     * @brief Applies the current temperature strategy if one is set.
     * Can be triggered after toggling or sensor update.
     */
    void applyTemperatureStrategy() {
        if (strategy) strategy->apply();
    }

    /**
     * @brief Returns the device type as a string.
     * @return "Thermostat"
     */
    std::string getType() const override {
        return "Thermostat";
    }

    /**
     * @brief Sets a specific temperature strategy manually (used on creation).
     * @param s Pointer to a TemperatureStrategy instance
     */
    void setStrategy(TemperatureStrategy* s) {
        strategy = s;
    }

    /**
     * @brief Toggles the thermostat state and applies strategy if turned on.
     */
    void toggle() override {
        SmartDevice::toggle();
        if (strategy && getState()) {
            strategy->apply();
        }
    }

    /**
     * @brief Destructor cleans up strategy to avoid memory leaks.
     */
    ~Thermostat() override {
        delete strategy;
    }
};

#endif // THERMOSTAT_H
