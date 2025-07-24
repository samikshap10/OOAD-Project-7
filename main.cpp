/**
 * @file main.cpp
 * @brief Command-line interface for SmartHomeSim: a C++ simulator for smart device control.
 *
 * This file implements the main user interface for interacting with the SmartHomeSim system.
 * 
 * Key OO Design Patterns Used:
 * - Factory Pattern: for dynamic creation of smart devices (DeviceFactory)
 * - Observer Pattern: for logging device state changes and reacting to sensor input (DeviceLogger, Sensor)
 * - Strategy Pattern: for both thermostat temperature handling and time-based scheduling (EcoMode, ComfortMode, OneTimeSchedule, etc.)
 *
 * Third-Party Elements:
 * - None. All code is part of the SmartHomeSim simulation.
 *
 * Date: 07/15/2025
 */

#include <iostream>
#include <string>

// Core project headers
#include "controllers/DeviceController.h"
#include "controllers/Scheduler.h"
#include "utils/DeviceFactory.h"
#include "observers/DeviceLogger.h"
#include "models/strategies/EcoMode.h"
#include "models/strategies/ComfortMode.h"
#include "models/Thermostat.h"
#include "models/sensor/Sensor.h"
#include "strategies/scheduling/OneTimeSchedule.h"
#include "strategies/scheduling/PeriodicSchedule.h"
#include "strategies/scheduling/DelayedSchedule.h"

/**
 * @brief Prints the main CLI menu.
 */
void printMenu() {
    std::cout << "\n===== SmartHomeSim CLI Menu =====\n";
    std::cout << "Commands:\n";
    std::cout << "  <name>      - Toggle a device on/off by name\n";
    std::cout << "  add         - Add a new smart device\n";
    std::cout << "  sensor      - Simulate a sensor event\n";
    std::cout << "  list        - Show all registered devices\n";
    std::cout << "  tick        - Advance simulated time by 1 second\n";
    std::cout << "  schedule    - Schedule device action using a timing strategy\n";
    std::cout << "  logs        - Show logged device activity\n";
    std::cout << "  reset       - Reset simulation time and tasks\n";
    std::cout << "  exit        - Quit the simulation\n";
    std::cout << "==================================\n";
}

/**
 * @brief Main entry point for SmartHomeSim.
 */
int main() {
    int currentTime = 0;
    DeviceController controller;

    // Initial device setup
    SmartDevice* light = DeviceFactory::createDevice("Light", "LivingRoom Light");
    SmartDevice* fan = DeviceFactory::createDevice("Fan", "Bedroom Fan");
    SmartDevice* thermostat = DeviceFactory::createDevice("Thermostat", "Hallway Thermostat");
    controller.addDevice(light);
    controller.addDevice(fan);
    controller.addDevice(thermostat);

    // Attach logger to all devices
    DeviceLogger* logger = new DeviceLogger();
    light->attach(logger);
    fan->attach(logger);
    thermostat->attach(logger);

    // Thermostat uses Strategy Pattern (EcoMode)
    Thermostat* t = dynamic_cast<Thermostat*>(thermostat);
    if (t) t->setStrategy(new EcoMode());

    // Sensor setup (Observer Pattern)
    Sensor sensor;
    sensor.subscribe(light);
    sensor.subscribe(fan);
    sensor.subscribe(thermostat);

    // Scheduler setup (Strategy Pattern for time-based behavior)
    Scheduler scheduler(&controller.getAllDevices());

    // CLI Loop
    std::string command;
    while (true) {
        printMenu();
        std::cout << "\nEnter command : ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        else if (command == "add") {
            std::string type, name;
            std::cout << "Enter device type (Light/Fan/Thermostat): ";
            std::getline(std::cin, type);
            std::cout << "Enter device name: ";
            std::getline(std::cin, name);
            SmartDevice* newDevice = DeviceFactory::createDevice(type, name);
            if (newDevice) {
                controller.addDevice(newDevice);
                newDevice->attach(logger);
                sensor.subscribe(newDevice);
                if (type == "Thermostat") {
                    Thermostat* th = dynamic_cast<Thermostat*>(newDevice);
                    if (th) th->setStrategy(new EcoMode());
                }
                std::cout << "[System] " << type << " \"" << name << "\" added successfully.\n";
            } else {
                std::cout << "[Error] Invalid device type.\n";
            }
        }

        else if (command == "sensor") {
            int value;
            std::cout << "Enter sensor value (e.g., temperature): ";
            std::cin >> value;
            std::cin.ignore();
            sensor.trigger(value);
        }

        else if (command == "logs") {
            logger->printLogs();
        }

        else if (command == "list") {
            controller.listDevices();
        }

        else if (command == "schedule") {
            std::string deviceName, state, strategyType;
            int timeValue;
            std::cout << "Enter device name: ";
            std::getline(std::cin, deviceName);
            std::cout << "Enter desired state (on/off): ";
            std::getline(std::cin, state);
            std::cout << "Choose strategy (one-time / periodic / delayed): ";
            std::getline(std::cin, strategyType);
            std::cout << "Enter time value (in seconds): ";
            std::cin >> timeValue;
            std::cin.ignore();

            SchedulingStrategy* strategy = nullptr;
            if (strategyType == "one-time")
                strategy = new OneTimeSchedule(timeValue);
            else if (strategyType == "periodic")
                strategy = new PeriodicSchedule(timeValue);
            else if (strategyType == "delayed")
                strategy = new DelayedSchedule(currentTime + timeValue);
            else {
                std::cout << "[Error] Invalid strategy type.\n";
                continue;
            }
            scheduler.addTask(deviceName, state == "on", strategy);
        }

        else if (command == "tick") {
            currentTime++;
            std::cout << "[Tick] Simulated time: " << currentTime << "s\n";
            scheduler.update(currentTime);
        }

        else if (command == "reset") {
            currentTime = 0;
            scheduler.clearTasks();
            std::cout << "[System] Simulation reset.\n";
        }

        else {
            controller.toggleDevice(command);
        }
    }

    delete logger;
    return 0;
}
