/**
 * @file Fan.h
 * @brief Concrete implementation of a smart fan device in SmartHomeSim.
 *
 * The `Fan` class inherits from `SmartDevice` and implements logic to respond to
 * environmental sensor input. When the temperature exceeds a threshold (28°C), 
 * the fan turns ON; otherwise, it turns OFF.
 *
 * Key Features:
 * - Implements `getType()` for device identification
 * - Reacts to temperature sensor input using Observer behavior
 *
 * Design Patterns:
 * - Inherits from `SmartDevice` (abstract base class)
 * - Uses Observer pattern to receive sensor-triggered updates
 *
 */

#ifndef FAN_H
#define FAN_H

#include "SmartDevice.h"

class Fan : public SmartDevice {
public:
    /**
     * @brief Constructs a smart fan with a given name.
     * @param name The display name of the fan device
     */
    Fan(const std::string& name) : SmartDevice(name) {}

    /**
     * @brief Returns the device type as a string ("Fan").
     * @return "Fan"
     */
    std::string getType() const override { return "Fan"; }

    /**
     * @brief Responds to sensor input (e.g., temperature).
     * 
     * Turns the fan ON if the temperature exceeds 28°C,
     * and turns it OFF otherwise.
     * 
     * @param value The value received from the sensor (e.g., temperature)
     */
    void onSensorTriggered(int value) override;
};

/**
 * @brief Inline implementation of the sensor-trigger response for Fan.
 * 
 * Turns ON if temperature > 28, OFF otherwise.
 */
inline void Fan::onSensorTriggered(int value) {
    if (value > 28) {
        std::cout << "[Fan] " << getName() << " is turning ON due to high temperature.\n";
        setState(true);
    } else {
        std::cout << "[Fan] " << getName() << " is turning OFF (comfortable temp).\n";
        setState(false);
    }
}

#endif // FAN_H
