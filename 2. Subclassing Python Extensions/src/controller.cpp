#include <chrono>
#include <condition_variable>
#include <memory>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

#include "controller.h"

using namespace std::chrono_literals;

Controller::Controller(std::shared_ptr<Cooler> cooler) :
        cooler_(std::move(cooler)),
        state_{Event::TEMP_OK}
{
}


void Controller::SetCooler(std::shared_ptr<Cooler> cooler)
{
    cooler_ = std::move(cooler);
}

void Controller::Signal(Controller::Event event)
{
    std::cout << "[Controller] Received event " << event << std::endl;
    switch (event)
    {
        case Event::TEMP_LOW:
        case Event::TEMP_HIGH:
        case Event::TEMP_OK:
            state_.temperature = event;
            break;
        default:
            break;
    }
    HandleStateChange();
}

void Controller::HandleStateChange()
{
    if (cooler_)
    {
        switch (state_.temperature)
        {
            case Event::TEMP_HIGH:
                cooler_->On();
                break;
            case Event::TEMP_LOW:
                cooler_->Off();
                break;
            default:
                break;
        }
    }
}

std::shared_ptr<Cooler> Controller::GetCooler()
{
    return cooler_;
}

std::string& ToString(Controller::Event event)
{
    static std::map<Controller::Event, std::string> stateStrings;

    if (stateStrings.empty())
    {
        auto extractEnumSymbol = [](const std::string& s)
        {
            std::size_t last_colon = s.rfind(':');
            return (last_colon == std::string::npos) ? s : s.substr(last_colon + 1);
        };
#define ADD_ENUM_STRING(x) stateStrings[x] = extractEnumSymbol(std::string(#x))
        ADD_ENUM_STRING(Controller::Event::TEMP_OK);
        ADD_ENUM_STRING(Controller::Event::TEMP_LOW);
        ADD_ENUM_STRING(Controller::Event::TEMP_HIGH);
#undef ADD_ENUM_STRING
    }
    return stateStrings[event];
}

std::ostream& operator<<(std::ostream& ostream, Controller::Event event)
{
    return ostream << ToString(event);
}
