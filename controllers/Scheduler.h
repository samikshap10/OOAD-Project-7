/**
 * @file Scheduler.h
 * @brief Scheduler class for SmartHomeSim: handles scheduled smart device actions.
 *
 * This file defines the Scheduler class and the ScheduledTask struct, which collectively manage
 * and execute timed device actions using the Strategy Pattern.
 *
 * Design Pattern:
 * - Strategy Pattern: Allows scheduling behavior to vary dynamically at runtime through concrete
 *   strategy classes like OneTimeSchedule, PeriodicSchedule, and DelayedSchedule.
 *
 * Responsibilities:
 * - Store scheduled tasks for devices
 * - Evaluate tasks on each simulation tick
 * - Trigger device state changes when appropriate
 * - Clean up dynamically allocated strategies
 *
 * Dependencies:
 * - SmartDevice.h: Abstract base class for all devices
 * - SchedulingStrategy.h: Abstract base class for time-based strategies
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../models/SmartDevice.h"
#include "../models/strategies/scheduling/SchedulingStrategy.h"

/**
 * @brief Represents a task to change a device's state at a scheduled time.
 *
 * Acts as the context object in the Strategy Pattern, holding:
 * - the target device's name
 * - whether it should be turned ON or OFF
 * - the scheduling strategy that determines when to execute
 */
struct ScheduledTask {
    std::string deviceName;                  ///< Name of the target device
    bool turnOn;                             ///< Desired state (true = ON, false = OFF)
    SchedulingStrategy* strategy;            ///< Strategy determining when task should trigger
    bool completed = false;                  ///< Flag to determine if the task is done
};

/**
 * @brief Scheduler manages timed device actions based on simulated time.
 *
 * The Scheduler keeps track of all scheduled tasks and triggers device actions
 * by delegating the time-check logic to the strategy associated with each task.
 */
class Scheduler {
private:
    std::vector<ScheduledTask> tasks;               ///< List of all active scheduled tasks
    std::vector<SmartDevice*>* devices;             ///< Pointer to the global device list

public:
    /**
     * @brief Constructs the Scheduler.
     * @param allDevices Pointer to the main device list managed externally
     */
    Scheduler(std::vector<SmartDevice*>* allDevices) : devices(allDevices) {}

    /**
     * @brief Adds a new scheduled task with a specific strategy.
     * @param name Name of the target device
     * @param turnOn Whether to turn the device on (true) or off (false)
     * @param strategy Pointer to the scheduling strategy
     */
    void addTask(const std::string& name, bool turnOn, SchedulingStrategy* strategy) {
        tasks.push_back(ScheduledTask{name, turnOn, strategy});
    }

    /**
     * @brief Clears all scheduled tasks and deletes associated strategies.
     *
     * Called during reset to free memory and restart the schedule list.
     */
    void clearTasks() {
        for (auto& task : tasks) {
            delete task.strategy; // Free strategy memory
        }
        tasks.clear();
        std::cout << "[Scheduler] All scheduled tasks cleared.\n";
    }

    /**
     * @brief Called on each simulation tick to evaluate and trigger tasks.
     * @param currentTime The current simulated time in seconds
     */
    void update(int currentTime) {
        for (auto& task : tasks) {
            if (!task.completed && task.strategy->shouldTrigger(currentTime)) {
                SmartDevice* device = findDeviceByName(task.deviceName);
                if (device) {
                    device->setState(task.turnOn);
                    std::cout << "[Scheduler] " << task.deviceName << " turned "
                              << (task.turnOn ? "ON" : "OFF") << " at time " << currentTime << "s\n";
                    task.completed = task.strategy->isDone();
                }
            }
        }
    }

private:
    /**
     * @brief Finds a device by name from the device list.
     * @param name The name of the device to locate
     * @return Pointer to the SmartDevice, or nullptr if not found
     */
    SmartDevice* findDeviceByName(const std::string& name) {
        for (auto device : *devices) {
            if (device->getName() == name) {
                return device;
            }
        }
        return nullptr;
    }
};

#endif // SCHEDULER_H
