
#include <chrono>
#include <iostream>

#include "room.h"

Room::Room(Airco& airco) :
        airco_(airco),
        temperature_(20.0),
        temperature_step_(0.1),
        temp_step_sign_(1.0),
        running_(false)
{
}

void Room::Start()
{
    auto cb = [this](bool cooler_is_running)
    {
        std::cout << "[Room Callback] Room is " << (cooler_is_running ? "cooling down" : "heating up") << std::endl;
        if (cooler_is_running)
        {
            temp_step_sign_ = -1.0;
        }
        else
        {
            temp_step_sign_ = 1.0;
        }
    };
    airco_.add_callback(cb);
    airco_.start();
    running_ = true;
    std::cout << "[Room] Starting airco" << std::endl;
    cycle_thread_ = std::thread(&Room::cycle_, this);
}

void Room::Stop()
{
    running_ = false;
    cycle_thread_.join();
}

void Room::cycle_()
{
    while (running_)
    {
        temperature_ += temp_step_sign_ * temperature_step_;
        std::cout << "[Room] Temperature is " << temperature_  << " degrees." << std::endl;
        airco_.temperature(temperature_);
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(500ms);
        }
    }
}
