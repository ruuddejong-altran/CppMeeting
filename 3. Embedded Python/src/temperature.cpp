#include <iostream>
#include <map>
#include "temperature.h"

std::string& ToString(TemperatureSignal signal)
{
    static std::map<TemperatureSignal, std::string> stateStrings;

    if (stateStrings.empty())
    {
        auto extractEnumSymbol = [](const std::string& s)
        {
            std::size_t last_colon = s.rfind(':');
            return (last_colon == std::string::npos) ? s : s.substr(last_colon + 1);
        };
#define ADD_ENUM_STRING(x) stateStrings[x] = extractEnumSymbol(std::string(#x))
        ADD_ENUM_STRING(TemperatureSignal::TEMP_OK);
        ADD_ENUM_STRING(TemperatureSignal::TEMP_LOW);
        ADD_ENUM_STRING(TemperatureSignal::TEMP_HIGH);
#undef ADD_ENUM_STRING
    }
    return stateStrings[signal];
}

std::ostream& operator<<(std::ostream& ostream, TemperatureSignal signal)
{
    return ostream << ToString(signal);
}

