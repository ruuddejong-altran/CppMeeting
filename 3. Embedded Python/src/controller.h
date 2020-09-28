#ifndef AIRCO_CONTROLLER_H
#define AIRCO_CONTROLLER_H

#include "cooler.h"

class Controller
{
public:
    enum class Event {
        TEMP_HIGH,
        TEMP_OK,
        TEMP_LOW,
    };
    explicit Controller(std::shared_ptr<Cooler> cooler = nullptr);
    virtual ~Controller() = default;
    virtual void SetCooler(std::shared_ptr<Cooler> cooler);
    virtual std::shared_ptr<Cooler> GetCooler();
    virtual void Signal(Event event);

protected:
    virtual void HandleStateChange();
    std::shared_ptr<Cooler> cooler_;
    struct
    {
        Event temperature;
    } state_;
};

std::string& ToString(Controller::Event event);
std::ostream& operator<<(std::ostream& ostream, Controller::Event event);

#endif //AIRCO_CONTROLLER_H
