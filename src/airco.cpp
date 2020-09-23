#include <iostream>
#include <map>

#include "airco.h"

Airco::Airco() : state_(Airco::State::Off), transition_callbacks_()
{
}

void Airco::On()
{
    ChangeState_(State::On);
}

void Airco::Off()
{
    ChangeState_(State::Off);
}

Airco::State Airco::GetState() const
{
    return state_;
}


void Airco::AddCallback(const Airco::CallbackFunctionType& func)
{
    transition_callbacks_.push_back(func);
}

void Airco::ChangeState_(Airco::State new_state)
{
    if (new_state != state_)
    {
        std::cout << "[Airco] State: " << new_state << "." << std::endl;
        auto prev_state = state_;
        state_ = new_state;
        for (auto& f : transition_callbacks_)
        {
            f(prev_state, new_state);
        }

    }
}

std::string& ToString(Airco::State state)
{
    static std::map<Airco::State, std::string> stateStrings;

    if (stateStrings.empty())
    {
        auto extractEnumSymbol = [](const std::string& s)
        {
            std::size_t last_colon = s.rfind(':');
            return (last_colon == std::string::npos) ? s : s.substr(last_colon + 1);
        };
#define ADD_ENUM_STRING(x) stateStrings[x] = extractEnumSymbol(std::string(#x))
        ADD_ENUM_STRING(Airco::State::Off);
        ADD_ENUM_STRING(Airco::State::On);
#undef ADD_ENUM_STRING
    }
    return stateStrings[state];
}

std::ostream& operator<<(std::ostream& ostream, Airco::State state)
{
    return ostream << ToString(state);
}

