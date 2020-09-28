#ifndef AIRCO_ROOM_H
#define AIRCO_ROOM_H

#include <memory>
#include <thread>
#include "airco.h"

class Room
{
public:
    explicit Room(std::shared_ptr<Airco> airco = nullptr);
    ~Room() = default;
    virtual void SetAirco(std::shared_ptr<Airco> airco);
    virtual std::shared_ptr<Airco> GetAirco();
    virtual void Start();
    virtual void Stop();

private:
    std::shared_ptr<Airco> airco_;
    float temperature_;
    float temperature_step_;
    float temp_step_sign_;
    bool running_;
    std::thread cycle_thread_;
    void cycle_();
};


#endif //AIRCO_ROOM_H
