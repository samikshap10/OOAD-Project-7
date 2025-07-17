/**
 * @file SmartDevice.h
 * @brief Abstract base class for all smart devices in the SmartHomeSim system.
 *
 * This class provides the core interface and shared functionality for all smart home devices,
 * such as Lights, Fans, and Thermostats. It defines a uniform interface for toggling device state,
 * observing sensor inputs, and notifying observers about state changes.
 *
 * Key Features:
 * - Implements the Subject role in the Observer pattern
 * - Allows attaching observers (e.g., loggers)
 * - Provides toggle and setState functionality with automatic notifications
 * - Requires derived classes to implement sensor-trigger behavior and device type identification
 *
 * Design Patterns:
 * - Observer Pattern: This class is the subject being observed by `Observer` instances
 * - Polymorphism: Provides a virtual interface for handling sensor input and identifying type
 */

#ifndef SMART_DEVICE_H
#define SMART_DEVICE_H

#include <string>
#include <vector>
#include "../observers/Observer.h"

class SmartDevice {
protected:
    std::string name;                     ///< Name of the device (e.g., "LivingRoom Light")
    bool isOn;                            ///< Current state of the device (true = on, false = off)
    std::vector<Observer*> observers;     ///< List of attached observers

public:
    /**
     * @brief Constructor that initializes device with a given name and default state off.
     * @param deviceName Name of the smart device
     */
    SmartDevice(const std::string& deviceName) : name(deviceName), isOn(false) {}

    /**
     * @brief Virtual destructor to allow proper cleanup in derived classes.
     */
    virtual ~SmartDevice() {}

    /**
     * @brief Pure virtual function to handle sensor-triggered behavior.
     *        Each derived device class must define how it reacts to a sensor value.
     * @param sensorValue The value triggered by a sensor (e.g., temperature)
     */
    virtual void onSensorTriggered(int sensorValue) = 0;

    /**
     * @brief Toggles the device's on/off state and notifies observers of the change.
     */
    virtual void toggle() {
        isOn = !isOn;
        notify();
    }

    /**
     * @brief Sets the device's on/off state and notifies observers if the state changes.
     * @param on New state to set (true for on, false for off)
     */
    void setState(bool on) {
        if (isOn != on) {
            isOn = on;
            notify();
        }
    }

    /**
     * @brief Notifies all registered observers that the device state has changed.
     */
    void notify() {
        for (auto* o : observers)
            o->update(this);
    }

    /**
     * @brief Pure virtual function to get the type of the device (e.g., "Light", "Fan").
     * @return A string representing the device type
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Gets the name of the device.
     * @return The name string
     */
    std::string getName() const { return name; }

    /**
     * @brief Gets the current on/off state of the device.
     * @return True if the device is on, false otherwise
     */
    bool getState() const { return isOn; }

    /**
     * @brief Attaches an observer to this device for state change notifications.
     * @param o Pointer to an Observer instance
     */
    void attach(Observer* o) { observers.push_back(o); }
};

#endif // SMART_DEVICE_H
