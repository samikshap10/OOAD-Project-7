/**
 * @file main.cpp
 * @brief Command-line interface for SmartHomeSim: a C++ simulator for smart device control.
 *
 * This file implements the main user interface for interacting with the SmartHomeSim system. It allows
 * users to manage and simulate the behavior of smart home devices such as lights, fans, and thermostats.
 * The CLI supports adding new devices, toggling them on/off, simulating sensor events, and viewing logs.
 *
 * Key Features:
 * - Uses the Factory Pattern to instantiate different types of smart devices
 * - Uses the Observer Pattern for device logging and sensor notifications
 * - Uses the Strategy Pattern to define customizable thermostat behavior (EcoMode/ComfortMode)
 * - Interacts with a centralized DeviceController to manage devices
 * - Provides a user-friendly CLI menu with interactive prompts
 *
 * Classes and Components Involved:
 * - DeviceController: Manages the list of smart devices and toggles their states
 * - DeviceFactory: Creates devices based on type strings (Light, Fan, Thermostat)
 * - DeviceLogger: Observes and logs device events (turn on/off, sensor reactions)
 * - Sensor: Notifies subscribed devices of simulated environmental changes
 * - Thermostat: Supports dynamic strategy assignment for temperature-based logic
 *
 * Date: 07/15/2025
 */

#include <iostream>
#include <string>

// Include custom project headers
#include "controllers/DeviceController.h"
#include "utils/DeviceFactory.h"
#include "observers/DeviceLogger.h"
#include "models/strategies/EcoMode.h"
#include "models/strategies/ComfortMode.h"
#include "models/Thermostat.h"
#include "models/sensor/Sensor.h"

/**
 * @brief Prints the main menu displayed in the SmartHomeSim CLI.
 */
void printMenu() {
    std::cout << "\n===== SmartHomeSim CLI Menu =====\n";
    std::cout << "Commands:\n";
    std::cout << "  <name>    - Toggle a device on/off by entering its name directly\n";
    std::cout << "  add       - Add a new smart device to the system\n";
    std::cout << "  sensor    - Simulate sensor input (e.g., temperature)\n";
    std::cout << "  list      - Show all devices currently in the system\n";
    std::cout << "  logs      - Display log of device actions\n";
    std::cout << "  exit      - Exit the simulation\n";
    std::cout << "==================================\n";
}

/**
 * @brief Entry point for the SmartHomeSim CLI application.
 * 
 * This function:
 * - Initializes default devices (Light, Fan, Thermostat)
 * - Attaches observers (Logger)
 * - Applies strategy pattern for thermostat behavior (EcoMode)
 * - Subscribes devices to sensor for triggering behavior
 * - Runs a loop to handle user commands through a command-line interface
 * 
 * @return int 0 on successful exit
 */
int main() {
    // Controller manages all smart devices
    DeviceController controller;

    // --- Initial Setup: Create and register core smart devices ---
    SmartDevice* light = DeviceFactory::createDevice("Light", "LivingRoom Light");
    SmartDevice* fan = DeviceFactory::createDevice("Fan", "Bedroom Fan");
    SmartDevice* thermostat = DeviceFactory::createDevice("Thermostat", "Hallway Thermostat");

    controller.addDevice(light);
    controller.addDevice(fan);
    controller.addDevice(thermostat);

    // --- Observer Setup: Attach logger to each device ---
    DeviceLogger* logger = new DeviceLogger();
    light->attach(logger);
    fan->attach(logger);
    thermostat->attach(logger);

    // --- Strategy Pattern: Set thermostat strategy to EcoMode ---
    Thermostat* t = dynamic_cast<Thermostat*>(thermostat);
    if (t) {
        t->setStrategy(new EcoMode());
    }

    // --- Sensor Setup: Subscribes thermostat to temperature changes ---
    Sensor sensor;
    sensor.subscribe(thermostat);

    // --- Command Line Interface Loop ---
    std::string command;
    while (true) {
        printMenu(); // Print menu at the start of each loop
        std::cout << "\nEnter command : ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break; // Exit simulation
        }
        else if (command == "add") {
            // Prompt for device type and name
            std::string type, name;
            std::cout << "Enter device type (Light/Fan/Thermostat): ";
            std::getline(std::cin, type);
            std::cout << "Enter device name: ";
            std::getline(std::cin, name);

            // Create and add device
            SmartDevice* newDevice = DeviceFactory::createDevice(type, name);
            if (newDevice) {
                controller.addDevice(newDevice);
                newDevice->attach(logger);      // Attach logger
                sensor.subscribe(newDevice);    // Subscribe to sensor
                std::cout << "[System] " << type << " \"" << name << "\" added successfully.\n";

                // Default to EcoMode strategy for thermostats
                if (type == "Thermostat") {
                    Thermostat* th = dynamic_cast<Thermostat*>(newDevice);
                    if (th) {
                        th->setStrategy(new EcoMode());
                    }
                }
            } else {
                std::cout << "[Error] Invalid device type. Valid types: Light, Fan, Thermostat.\n";
            }
        }
        else if (command == "sensor") {
            // Trigger a sensor event with user-provided value
            int value;
            std::cout << "Enter sensor value (e.g., temperature): ";
            std::cin >> value;
            std::cin.ignore(); // Clear newline from input buffer
            sensor.trigger(value);
        }
        else if (command == "logs") {
            // Print all logs captured by the logger
            logger->printLogs();
        }
        else if (command == "list") {
            // Show list of all devices
            controller.listDevices();
        }
        else {
            // Attempt to toggle a device by name
            controller.toggleDevice(command);
        }
    }

    // Cleanup resources
    delete logger;  // Future: implement full cleanup in controller
    return 0;
}
