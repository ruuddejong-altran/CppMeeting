#include <iostream>

#include "airco.h"

Airco::Airco(Controller& controller, Thermostat& thermostat) :
        controller_(controller),
        thermostat_(thermostat),
        running_(false)
{
}

void Airco::start()
{
    std::cout << "[Airco] Starting" << std::endl;
    running_ = true;
}

void Airco::stop()
{
    running_ = false;
    std::cout << "[Airco] Stopped" << std::endl;
}

void Airco::temperature(double temp)
{
    std::cout << "[Airco] Received temperature " << temp << std::endl;
    if (running_)
    {
        controller_.signal(thermostat_.temperature(temp));
    }
}

void Airco::add_callback(const Controller::CallbackFunctionType callback)
{
    controller_.add_callback(callback);
}

void Airco::set_temperature_range(double low_temp, double high_temp)
{
    thermostat_.set_temperature_range(low_temp, high_temp);
}

std::pair<double, double> Airco::get_temperature_range()
{
    return thermostat_.get_temperature_range();
}
