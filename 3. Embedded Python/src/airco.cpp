#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <utility>

#include "airco.h"

using namespace std::chrono_literals;

Airco::Airco(double low_temperature, double high_temperature,
             std::shared_ptr<Controller> controller, std::shared_ptr<Cooler> cooler) :
        temperature_low_(low_temperature),
        temperature_high_(high_temperature),
        controller_(std::move(controller)),
        cooler_(std::move(cooler)),
        running_(false)
{
}

bool Airco::Start()
{
    bool can_start = true;
    std::vector<std::string> error_messages;
    if (temperature_high_ <= temperature_low_)
    {
        can_start = false;
        std::stringstream ss;
        ss << "[Airco] Invalid temperature range: low = " << temperature_low_ << ", high = " << temperature_high_;
        error_messages.emplace_back(ss.str());
    }
    if (! controller_)
    {
        can_start = false;
        error_messages.emplace_back("[Airco] Start error: controller not defined.");
    }
    if (! cooler_)
    {
        can_start = false;
        error_messages.emplace_back("[Airco] Start error: cooler not defined.");
    }
    if (can_start)
    {
        std::cout << "[Airco] Starting" << std::endl;
        controller_->SetCooler(cooler_);
        running_ = true;
    }
    else
    {
        for (auto& message :  error_messages)
        {
            std::cout << message << std::endl;
        }
    }
    return can_start;
}

void Airco::Stop()
{
    running_ = false;
    std::cout << "[Airco] Stopped" << std::endl;
}

void Airco::Temperature(double temperature)
{
    std::cout << "[Airco] Received temperature " << temperature << std::endl;
    if (running_)
    {
        Controller::Event temp_event = Controller::Event::TEMP_OK;
        if (temperature <= temperature_low_)
        {
            temp_event = Controller::Event::TEMP_LOW;
        }
        else if (temperature >= temperature_high_)
        {
            temp_event = Controller::Event::TEMP_HIGH;
        }
        controller_->Signal(temp_event);
    }
}

void Airco::AddCallback(const Cooler::CallbackFunctionType& callback)
{
    if (cooler_)
    {
        cooler_->AddCallback(callback);
    }
    else
    {
        std::cout << "[Airco] AddCallback error: cooler not defined" << std::endl;
    }
}

void Airco::SetController(std::shared_ptr<Controller> controller)
{
    controller_ = std::move(controller);
}

void Airco::SetCooler(std::shared_ptr<Cooler> cooler)
{
    cooler_ = std::move(cooler);
}

void Airco::SetTemperatureRange(double low_temp, double high_temp)
{
    if (low_temp < high_temp)
    {
        temperature_low_ = low_temp;
        temperature_high_ = high_temp;
    }
    else
    {
        std::cout << "[Airco] Invalid temperature range: low = " << low_temp << ", high = " << high_temp << std::endl;
    }
}

std::shared_ptr<Controller> Airco::GetController()
{
    return controller_;
}

std::shared_ptr<Cooler> Airco::GetCooler()
{
    return cooler_;
}

std::pair<double, double> Airco::GetTemperatureRange()
{
    return std::pair<double, double>(temperature_low_, temperature_high_);
}
