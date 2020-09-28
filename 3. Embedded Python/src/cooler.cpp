#include <iostream>
#include <map>

#include "cooler.h"

Cooler::Cooler() : state_(Cooler::State::Off), callbacks_()
{
}

void Cooler::On()
{
    ChangeState_(State::On);
}

void Cooler::Off()
{
    ChangeState_(State::Off);
}

Cooler::State Cooler::GetState() const
{
    return state_;
}


void Cooler::AddCallback(const Cooler::CallbackFunctionType& func)
{
    callbacks_.push_back(func);
}

void Cooler::ChangeState_(Cooler::State new_state)
{
    if (new_state != state_)
    {
        std::cout << "[Cooler] State changed to: " << new_state << "." << std::endl;
        state_ = new_state;
        for (auto& f : callbacks_)
        {
            f(state_ == State::On);
        }
    }
}

std::string& ToString(Cooler::State state)
{
    static std::map<Cooler::State, std::string> stateStrings;

    if (stateStrings.empty())
    {
        auto extractEnumSymbol = [](const std::string& s)
        {
            std::size_t last_colon = s.rfind(':');
            return (last_colon == std::string::npos) ? s : s.substr(last_colon + 1);
        };
#define ADD_ENUM_STRING(x) stateStrings[x] = extractEnumSymbol(std::string(#x))
        ADD_ENUM_STRING(Cooler::State::Off);
        ADD_ENUM_STRING(Cooler::State::On);
#undef ADD_ENUM_STRING
    }
    return stateStrings[state];
}

std::ostream& operator<<(std::ostream& ostream, Cooler::State state)
{
    return ostream << ToString(state);
}

