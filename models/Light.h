/**
 * @file Light.h
 * @brief Concrete implementation of a smart light device in SmartHomeSim.
 *
 * The `Light` class inherits from `SmartDevice` and represents a basic smart light.
 * Currently, lights do not respond to sensor-triggered environmental changes
 * (e.g., temperature), but still receive updates to support future extensibility.
 *
 * Key Features:
 * - Implements `getType()` for device identification
 * - Logs sensor input receipt, even if no action is taken
 *
 * Design Patterns:
 * - Inherits from `SmartDevice` (abstract base class)
 * - Participates in the Observer Pattern via sensor notifications
 *
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "SmartDevice.h"

class Light : public SmartDevice {
public:
    /**
     * @brief Constructs a smart light with the given name.
     * @param name The display name of the light device
     */
    Light(const std::string& name) : SmartDevice(name) {}

    /**
     * @brief Returns the type of device.
     * @return "Light"
     */
    std::string getType() const override { return "Light"; }

    /**
     * @brief Handles sensor input (no behavior defined currently).
     * Logs that the light received the update but takes no action.
     *
     * @param value The value received from the sensor (e.g., temperature)
     */
    void onSensorTriggered(int value) override;
};

/**
 * @brief Inline definition for how the light responds to sensor input.
 *
 * Currently, the light logs the sensor value receipt but does not perform any action.
 */
inline void Light::onSensorTriggered(int value) {
    std::cout << "[Light] " << getName() << " received sensor update (no action).\n";
}

#endif // LIGHT_H
