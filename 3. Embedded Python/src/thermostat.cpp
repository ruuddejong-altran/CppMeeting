#include <iostream>

#include "temperature.h"
#include "thermostat.h"

Thermostat::Thermostat(double low_temp, double high_temp)
{
    set_temperature_range(low_temp, high_temp);
}

void Thermostat::set_temperature_range(double low_temp, double high_temp)
{
    if (low_temp < high_temp)
    {
        low_temperature_ = low_temp;
        high_temperature_ = high_temp;
    }
    else
    {
        std::cout << "[Thermostat] Error: low temperature " << low_temp << "is not strictly less than high temperature"
                  << high_temp << std::endl;
    }
}

std::pair<double, double> Thermostat::get_temperature_range()
{
    return std::pair<double, double>(low_temperature_, high_temperature_);
}

TemperatureSignal Thermostat::temperature(double temp)
{
    if (temp <= low_temperature_)
    {
        return TemperatureSignal::TEMP_LOW;
    }
    if (temp >= high_temperature_)
    {
        return TemperatureSignal::TEMP_HIGH;
    }
    return TemperatureSignal::TEMP_OK;
}
