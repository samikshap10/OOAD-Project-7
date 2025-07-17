/**
 * @file ComfortMode.h
 * @brief Concrete strategy class representing Comfort Mode for a thermostat.
 *
 * The `ComfortMode` class implements the `TemperatureStrategy` interface.
 * It represents a strategy where the thermostat prioritizes user comfort,
 * typically by maintaining a temperature around 72°F.
 *
 * This class is used in the Strategy Pattern to dynamically switch thermostat behavior
 * based on sensor input (e.g., high temperature triggers comfort mode).
 *
 * Design Pattern:
 * - Strategy Pattern: This is a concrete implementation of `TemperatureStrategy`
 */

#ifndef COMFORT_MODE_H
#define COMFORT_MODE_H

#include "TemperatureStrategy.h"
#include <iostream>

class ComfortMode : public TemperatureStrategy {
public:
    /**
     * @brief Applies the Comfort Mode temperature setting.
     * Outputs a message indicating the thermostat is set to a comfortable 72°F.
     */
    void apply() override {
        std::cout << "[Thermostat] Comfort Mode: Set to 72°F for comfort.\n";
    }
};

#endif // COMFORT_MODE_H
