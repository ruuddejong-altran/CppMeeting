//
// Created by Ruud on 23-9-2020.
//

#include "controller.h"

#include <utility>

Controller::Controller(std::shared_ptr<Airco> airco) : airco_(std::move(airco)), airco_allowed_(true),
                                                       callback_functions_()
{
    init_();
}

void Controller::init_()
{
    auto callback_func = [this](Airco::State old_state, Airco::State new_state)
    {
        airco_monitor_(old_state, new_state);
    };
    airco_->AddCallback(callback_func);
}

void Controller::TemperatureHigh()
{
    std::cout << "[Controller] Received temperature high signal." << std::endl;
    if (airco_allowed_)
    {
        std::cout << "[Controller] Switching airco ON." << std::endl;
        airco_->On();
    }
}

void Controller::TemperatureLow()
{
    std::cout << "[Controller] Received temperature low signal." << std::endl;
    std::cout << "[Controller] Switching airco OFF." << std::endl;
    airco_->Off();
}

void Controller::airco_monitor_(Airco::State old_state, Airco::State new_state)
{
    std::cout << "[Controller] Airco changed state to " << new_state << "." << std::endl;

    // Just relay to the callback functions registered here
    for (auto& func : callback_functions_)
    {
        func(old_state, new_state);
    }
}

void Controller::AddCallback(const Airco::CallbackFunctionType& callback_function)
{
    callback_functions_.push_back(callback_function);
}

