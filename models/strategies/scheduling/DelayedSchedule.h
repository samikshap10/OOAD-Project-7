/**
 * @file DelayedSchedule.h
 * @brief Concrete strategy for delayed device scheduling in SmartHomeSim.
 *
 * The DelayedSchedule class defines a scheduling strategy where a task triggers
 * once after a specified delay from the start of the simulation.
 *
 * Design Pattern:
 * - Strategy Pattern: Implements SchedulingStrategy for delayed triggering behavior.
 *
 * Responsibilities:
 * - Wait until the specified start time is reached
 * - Trigger once and mark as complete after triggering
 */

#ifndef DELAYED_SCHEDULE_H
#define DELAYED_SCHEDULE_H

#include "SchedulingStrategy.h"

/**
 * @brief Delayed trigger strategy: triggers once after a delay.
 */
class DelayedSchedule : public SchedulingStrategy {
private:
    int startTime;       ///< Time (in seconds) at which to trigger the task
    bool triggered = false; ///< Tracks whether the task has been triggered

public:
    /**
     * @brief Constructor for delayed schedule.
     * @param time The simulation time after which the task should trigger
     */
    DelayedSchedule(int time) : startTime(time) {}

    /**
     * @brief Checks if the current time has reached or passed the trigger time.
     * @param currentTime The current simulated time
     * @return true if the task should trigger now
     */
    bool shouldTrigger(int currentTime) override {
        if (!triggered && currentTime >= startTime) {
            triggered = true;
            return true;
        }
        return false;
    }

    /**
     * @brief Indicates whether the task has already triggered.
     * @return true if it has triggered, false otherwise
     */
    bool isDone() const override {
        return triggered;
    }
};

#endif // DELAYED_SCHEDULE_H
