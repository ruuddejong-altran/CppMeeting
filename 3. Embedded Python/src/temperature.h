#ifndef AIRCO_TEMPERATURE_H
#define AIRCO_TEMPERATURE_H

enum class TemperatureSignal
{
    TEMP_OK,
    TEMP_LOW,
    TEMP_HIGH
};

std::string& ToString(TemperatureSignal signal);
std::ostream& operator<<(std::ostream& ostream, TemperatureSignal signal);

#endif //AIRCO_TEMPERATURE_H
