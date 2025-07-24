/**
 * @file OneTimeSchedule.h
 * @brief Concrete strategy for one-time device scheduling in SmartHomeSim.
 *
 * The OneTimeSchedule class defines a scheduling strategy where a task triggers
 * exactly once at a specific simulated time. It is useful for one-off actions like
 * turning on a device at a designated moment.
 *
 * Design Pattern:
 * - Strategy Pattern: Implements SchedulingStrategy for one-time triggering behavior.
 *
 * Responsibilities:
 * - Trigger a task exactly once at the specified time
 * - Mark the task as complete after execution
 */

#ifndef ONE_TIME_SCHEDULE_H
#define ONE_TIME_SCHEDULE_H

#include "SchedulingStrategy.h"

/**
 * @brief One-time strategy for scheduling a single event.
 */
class OneTimeSchedule : public SchedulingStrategy {
private:
    int triggerTime;  ///< Time at which the task should trigger (in seconds)

public:
    /**
     * @brief Constructor for one-time schedule.
     * @param time The specific time (in seconds) to trigger the action
     */
    OneTimeSchedule(int time) : triggerTime(time) {}

    /**
     * @brief Checks whether the current time matches the trigger time.
     * @param currentTime The current simulated time
     * @return true if the task should trigger now
     */
    bool shouldTrigger(int currentTime) override {
        return currentTime == triggerTime;
    }

    /**
     * @brief Indicates the task should be considered complete after triggering.
     * @return true always
     */
    bool isDone() const override {
        return true;
    }
};

#endif // ONE_TIME_SCHEDULE_H
