/**
 * @file TemperatureStrategy.h
 * @brief Abstract base class for temperature control strategies in SmartHomeSim.
 *
 * The `TemperatureStrategy` class defines a common interface for thermostat behavior
 * that can be changed dynamically at runtime. Concrete implementations like `EcoMode`
 * and `ComfortMode` provide specific behaviors for different environmental or user needs.
 *
 * This class enables the use of the Strategy Design Pattern, allowing the thermostat
 * to delegate decision-making logic to interchangeable strategy objects.
 *
 * Design Pattern:
 * - Strategy Pattern: This is the abstract strategy interface.
 *
 */

#ifndef TEMPERATURE_STRATEGY_H
#define TEMPERATURE_STRATEGY_H

class TemperatureStrategy {
public:
    /**
     * @brief Applies the strategy-specific temperature setting.
     * Concrete classes must override this method to implement their behavior.
     */
    virtual void apply() = 0;

    /**
     * @brief Virtual destructor to allow proper cleanup in derived classes.
     */
    virtual ~TemperatureStrategy() {}
};

#endif // TEMPERATURE_STRATEGY_H
