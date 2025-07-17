#ifndef TEMPERATURE_STRATEGY_H
#define TEMPERATURE_STRATEGY_H

class TemperatureStrategy {
public:
    virtual void apply() = 0;
    virtual ~TemperatureStrategy() {}
};

#endif
