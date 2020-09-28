#include "thermostat.h"
#include <iostream>

Thermostat::Thermostat(Controller* controller, float low_temp, float high_temp) :
        controller_(controller), low_temp_(low_temp), high_temp_(high_temp)
{
}

void Thermostat::Connect(Controller *controller)
{
    controller_ = controller;
}

void Thermostat::Temperature(float temp)
{
    std::cout << "[Thermostat] Temperature: " << temp << std::endl;
    if (controller_)
    {
        if (temp > high_temp_)
        {
            controller_->TemperatureHigh();
        }
        else if (temp < low_temp_)
        {
            controller_->TemperatureLow();
        }
    }
}
