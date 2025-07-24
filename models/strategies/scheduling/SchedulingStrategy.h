/**
 * @file SchedulingStrategy.h
 * @brief Abstract strategy interface for scheduling device actions in SmartHomeSim.
 *
 * This header defines the base SchedulingStrategy class used by the Scheduler to determine
 * when device actions should trigger. Concrete subclasses implement specific time-based
 * behaviors (e.g., OneTimeSchedule, PeriodicSchedule, DelayedSchedule).
 *
 * Design Pattern:
 * - Strategy Pattern: Allows interchangeable scheduling policies at runtime.
 *
 * Responsibilities:
 * - Define an interface for time-based task evaluation
 * - Enable dynamic extension of scheduling logic without modifying the Scheduler
 */

#ifndef SCHEDULING_STRATEGY_H
#define SCHEDULING_STRATEGY_H

/**
 * @brief Abstract base class for time-based scheduling strategies.
 *
 * Subclasses must implement shouldTrigger() to specify when a device should change state.
 * The default isDone() assumes a one-time execution but may be overridden for periodic tasks.
 */
class SchedulingStrategy {
public:
    virtual ~SchedulingStrategy() {}

    /**
     * @brief Determines whether the action should be triggered at the given time.
     * @param currentTime The current simulated time
     * @return true if the task should execute, false otherwise
     */
    virtual bool shouldTrigger(int currentTime) = 0;

    /**
     * @brief Indicates whether the task is finished after triggering.
     * Default implementation assumes one-time schedule.
     * @return true if no longer needed, false if it should repeat
     */
    virtual bool isDone() const { return true; }
};

#endif // SCHEDULING_STRATEGY_H
