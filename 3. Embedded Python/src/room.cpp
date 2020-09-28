
#include <chrono>
#include <iostream>

#include "room.h"

Room::Room(std::shared_ptr<Airco> airco) :
        airco_(std::move(airco)),
        temperature_(20.0),
        temperature_step_(0.1),
        temp_step_sign_(1.0),
        running_(false)
{
}

void Room::SetAirco(std::shared_ptr<Airco> airco)
{
    airco_ = std::move(airco);
}

std::shared_ptr<Airco> Room::GetAirco()
{
    return airco_;
}

void Room::Start()
{
    if (airco_ && airco_->Start())
    {
        auto cb = [this](bool cooler_is_running)
        {
            std::cout << "[Callback] Cooler is" << (cooler_is_running ? "" : " not") << " running" << std::endl;
            if (cooler_is_running)
            {
                temp_step_sign_ = -1.0;
            }
            else
            {
                temp_step_sign_ = 1.0;
            }
        };
        airco_->AddCallback(cb);
        running_ = true;
        std::cout << "[Room] Starting airco" << std::endl;
        cycle_thread_ = std::thread(&Room::cycle_, this);
    }
    else
    {
        std::cout << "[Room] Cannot start airco" << std::endl;
    }
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
        airco_->Temperature(temperature_);
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(500ms);
        }
    }
}
