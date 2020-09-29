#include <iostream>

#include "controller.h"


Controller::Controller() :
        state_{TemperatureSignal::TEMP_OK},
        callbacks_()
{
}

void Controller::add_callback(Controller::CallbackFunctionType callback)
{
    callbacks_.push_back(callback);
}

void Controller::signal(TemperatureSignal a_signal)
{
    std::cout << "[Controller] Received event " << a_signal << std::endl;
    switch (a_signal)
    {
        case TemperatureSignal::TEMP_LOW:
        case TemperatureSignal::TEMP_HIGH:
        case TemperatureSignal::TEMP_OK:
            state_.temperature = a_signal;
            break;
        default:
            break;
    }
    handle_state_change();
}

void Controller::handle_state_change()
{
        switch (state_.temperature)
        {
            case TemperatureSignal::TEMP_HIGH:
                do_callbacks_with(true);
                break;
            case TemperatureSignal::TEMP_LOW:
                do_callbacks_with(false);
                break;
            default:
                break;
        }
}

void Controller::do_callbacks_with(bool value)
{
    for (auto& f : callbacks_)
    {
        f(value);
    }
}
