#ifndef AIRCO_CONTROLLER_H
#define AIRCO_CONTROLLER_H

#include <memory>

#include "airco.h"
class Controller
{
public:
    explicit Controller(std::shared_ptr<Airco> airco);
    ~Controller() = default;
    void TemperatureHigh();
    void TemperatureLow();
    void AddCallback(const Airco::CallbackFunctionType& callback_function);

private:
    std::shared_ptr<Airco> airco_;
    bool airco_allowed_;
    std::vector<Airco::CallbackFunctionType> callback_functions_;
    void airco_monitor_(Airco::State old_state, Airco::State new_state);

    void init_();
};


#endif //AIRCO_CONTROLLER_H
