#ifndef AIRCO_CONTROLLER_H
#define AIRCO_CONTROLLER_H

#include <functional>
#include "temperature.h"

class Controller
{
public:
    using CallbackFunctionType = std::function<void(bool)>;

    Controller();
    virtual ~Controller() = default;
    virtual void signal(TemperatureSignal signal);
    virtual void add_callback(CallbackFunctionType callback);

protected:
    virtual void handle_state_change();
    struct
    {
        TemperatureSignal temperature;
    } state_;

private:
    std::vector<CallbackFunctionType> callbacks_;
    void do_callbacks_with(bool value);
};

#endif //AIRCO_CONTROLLER_H
