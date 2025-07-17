#include <iostream>
#include <string>
#include "controllers/DeviceController.h"
#include "utils/DeviceFactory.h"
#include "observers/DeviceLogger.h"
#include "models/strategies/EcoMode.h"
#include "models/strategies/ComfortMode.h"
#include "models/Thermostat.h"
#include "models/sensor/Sensor.h"

int main() {
    DeviceController controller;

    // Initial setup
    SmartDevice* light = DeviceFactory::createDevice("Light", "LivingRoom Light");
    SmartDevice* fan = DeviceFactory::createDevice("Fan", "Bedroom Fan");
    SmartDevice* thermostat = DeviceFactory::createDevice("Thermostat", "Hallway Thermostat");

    controller.addDevice(light);
    controller.addDevice(fan);
    controller.addDevice(thermostat);

    DeviceLogger* logger = new DeviceLogger();
    light->attach(logger);
    fan->attach(logger);
    thermostat->attach(logger);

    // Thermostat strategy
    Thermostat* t = dynamic_cast<Thermostat*>(thermostat);
    if (t) t->setStrategy(new EcoMode());

    Sensor sensor;
    sensor.subscribe(thermostat);

    // Command line interface loop
    std::string command;
    while (true) {
        std::cout << "\nEnter command ('add', device name to toggle, or 'exit'): ";
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
                std::cout << "[System] " << type << " \"" << name << "\" added successfully.\n";

                // Optional: set EcoMode by default for new thermostats
                if (type == "Thermostat") {
                    Thermostat* th = dynamic_cast<Thermostat*>(newDevice);
                    if (th) th->setStrategy(new EcoMode());
                }
            } else {
                std::cout << "[Error] Invalid device type. Valid types: Light, Fan, Thermostat.\n";
            }
        }
        else if (command == "sensor") {
            sensor.trigger();  // Notify all listening devices
        }
        else {
            controller.toggleDevice(command);
        }
    }

    delete logger;
    // Controller should handle cleanup in future version
    return 0;
}
