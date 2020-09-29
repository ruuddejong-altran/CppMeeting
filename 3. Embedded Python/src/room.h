#ifndef AIRCO_ROOM_H
#define AIRCO_ROOM_H

#include <memory>
#include <thread>
#include "airco.h"

class Room
{
public:
    explicit Room(Airco& airco);
    ~Room() = default;
    virtual void Start();
    virtual void Stop();

private:
    Airco& airco_;
    float temperature_;
    float temperature_step_;
    float temp_step_sign_;
    bool running_;
    std::thread cycle_thread_;
    void cycle_();
};


#endif //AIRCO_ROOM_H
