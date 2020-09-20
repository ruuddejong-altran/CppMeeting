#include <iostream>
#include <map>

#include "light.h"

Light::Light(const std::string& name, Light::State state) : name_(name), state_(state)
{
}

Light::~Light()
{
}

std::string Light::GetName() const
{
    return name_;
}

void Light::SetName(const std::string& name)
{
    name_ = name;
}

Light::State Light::GetState() const
{
    return state_;
}

void Light::SetState(Light::State state)
{
    state_ = state;
}

std::string& ToString(Light::State state)
{
    static std::map<Light::State, std::string> stateStrings;

    if (stateStrings.empty())
    {
        auto extractEnumSymbol = [](const std::string& s)
        {
            std::size_t last_colon = s.rfind(':');
            return (last_colon == std::string::npos) ? s : s.substr(last_colon + 1);
        };
#define ADD_ENUM_STRING(x) stateStrings[x] = extractEnumSymbol(std::string(#x))
        ADD_ENUM_STRING(Light::State::Off);
        ADD_ENUM_STRING(Light::State::On);
        ADD_ENUM_STRING(Light::State::Flashing);
#undef ADD_ENUM_STRING
    }
    return stateStrings[state];
}

std::ostream& operator<<(std::ostream& ostream, const Light& light)
{
    return ostream << light.GetName() << ": " << ToString(light.GetState());
}
