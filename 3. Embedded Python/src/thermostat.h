#ifndef AIRCO_THERMOSTAT_H
#define AIRCO_THERMOSTAT_H

#include "controller.h"

class Controller;

class Thermostat
{
public:
    explicit Thermostat(Controller* controller = nullptr, float low_temp = 20.0, float high_temp = 21.0);
    virtual ~Thermostat() = default;
    void Connect(Controller* controller);
    void Temperature(float temp);

private:
    Controller* controller_;
    float low_temp_;
    float high_temp_;
};


#endif //AIRCO_THERMOSTAT_H
