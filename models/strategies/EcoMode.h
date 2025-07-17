/**
 * @file EcoMode.h
 * @brief Concrete strategy class representing Eco Mode for a thermostat.
 *
 * The `EcoMode` class implements the `TemperatureStrategy` interface and represents
 * a thermostat mode that prioritizes energy efficiency. It typically maintains
 * a lower temperature set point (e.g., 68°F) to reduce energy usage.
 *
 * This class is used as part of the Strategy Pattern to dynamically change
 * the thermostat's behavior in response to environmental changes.
 *
 * Design Pattern:
 * - Strategy Pattern: This is a concrete implementation of `TemperatureStrategy`
 *
 */

#ifndef ECO_MODE_H
#define ECO_MODE_H

#include "TemperatureStrategy.h"
#include <iostream>

class EcoMode : public TemperatureStrategy {
public:
    /**
     * @brief Applies the Eco Mode temperature setting.
     * Outputs a message indicating the thermostat is set to 68°F for energy saving.
     */
    void apply() override {
        std::cout << "[Thermostat] Eco Mode: Set to 68°F for energy saving.\n";
    }
};

#endif // ECO_MODE_H
