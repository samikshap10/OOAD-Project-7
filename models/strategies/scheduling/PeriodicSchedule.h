/**
 * @file PeriodicSchedule.h
 * @brief Concrete strategy for periodic device scheduling in SmartHomeSim.
 *
 * The PeriodicSchedule class defines a scheduling strategy where a task triggers repeatedly
 * at fixed time intervals. This is useful for simulating devices that need to operate on a
 * recurring basis (e.g., turning lights on every 5 seconds).
 *
 * Design Pattern:
 * - Strategy Pattern: Implements SchedulingStrategy for periodic triggering behavior.
 *
 * Responsibilities:
 * - Trigger device actions on a consistent interval
 * - Indicate that task should never be considered "done" (repeats forever)
 */

#ifndef PERIODIC_SCHEDULE_H
#define PERIODIC_SCHEDULE_H

#include "SchedulingStrategy.h"

/**
 * @brief Periodic strategy for scheduling repeated tasks.
 */
class PeriodicSchedule : public SchedulingStrategy {
private:
    int interval;  ///< Time interval (in seconds) between task executions

public:
    /**
     * @brief Constructor for periodic schedule.
     * @param intervalSeconds Interval in seconds at which to trigger
     */
    PeriodicSchedule(int intervalSeconds) : interval(intervalSeconds) {}

    /**
     * @brief Determines whether the current time matches the interval.
     * @param currentTime The current simulated time
     * @return true if the task should trigger at this time
     */
    bool shouldTrigger(int currentTime) override {
        return (currentTime % interval == 0);
    }

    /**
     * @brief Indicates that periodic tasks are never completed.
     * @return false always (indicating continuation)
     */
    bool isDone() const override {
        return false;
    }
};

#endif // PERIODIC_SCHEDULE_H
