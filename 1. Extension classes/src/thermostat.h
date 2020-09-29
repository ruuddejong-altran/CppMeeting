#ifndef AIRCO_THERMOSTAT_H
#define AIRCO_THERMOSTAT_H

#include "temperature.h"

class Thermostat {
public:
    explicit Thermostat(double low_temp = 20.0, double high_temp = 21.0);
    virtual ~Thermostat() = default;
    virtual void set_temperature_range(double low_temp, double high_temp);
    virtual std::pair<double, double> get_temperature_range();
    virtual TemperatureSignal temperature(double temp);

private:
    double low_temperature_;
    double high_temperature_;
};

#endif //AIRCO_THERMOSTAT_H
