
#include <chrono>
#include <iostream>

#include "room.h"

Room::Room(std::shared_ptr<Controller> controller_) : controller_(std::move(controller_)), running_(false),
                                                      cooling_(false), temperature_(200), temperature_delta_(1)
{
    init_();
}

void Room::init_()
{
    auto callback_func = [this](Airco::State old_state, Airco::State new_state)
    {
        airco_monitor_(old_state, new_state);
    };
    controller_->AddCallback(callback_func);
}

void Room::airco_monitor_(Airco::State old_state, Airco::State new_state)
{
    cooling_ = (new_state == Airco::State::On);
    std::cout << "[Room] " << (cooling_ ? "cooling down" : "warming up") << "." << std::endl;
}

void Room::start()
{
    running_ = true;
    cycle_thread_ = std::thread(&Room::cycle_, this);
}

void Room::stop()
{
    running_ = false;
    cycle_thread_.join();
}

void Room::cycle_()
{
    while (running_)
    {
        if (cooling_)
        {
            temperature_ -= temperature_delta_;
        }
        else
        {
            temperature_ += temperature_delta_;
        }
        std::cout << "[Room] Temperature is " << temperature_ / 10.0 << " degrees." << std::endl;
        if (temperature_ >= 210)  // 21 degrees
        {
            std::cout << "[Room] Signaling high temperature." << std::endl;
            controller_->TemperatureHigh();
        }
        else if (temperature_ < 200) // 20 degrees
        {
            std::cout << "[Room] Signaling low temperature." << std::endl;
            controller_->TemperatureLow();
        }
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);
        }
    }
}
