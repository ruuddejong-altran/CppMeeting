#ifndef AIRCO_AIRCO_H
#define AIRCO_AIRCO_H


#include "controller.h"
#include "thermostat.h"

class Airco
{
public:
    Airco(Controller& controller, Thermostat& thermostat);
    virtual ~Airco() = default;

    virtual void start();
    virtual void stop();
    virtual void temperature(double temp);
    virtual void set_temperature_range(double low_temp, double high_temp);
    virtual std::pair<double, double> get_temperature_range();
    virtual void add_callback(const Controller::CallbackFunctionType callback);

    virtual void set_controller(Controller* controller);
    virtual void set_thermostat(Thermostat* thermostat);

private:
    Controller* controller_;
    Thermostat* thermostat_;
    bool running_;
};


#endif //AIRCO_AIRCO_H

