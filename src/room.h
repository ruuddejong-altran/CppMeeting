#ifndef AIRCO_ROOM_H
#define AIRCO_ROOM_H

#include <memory>
#include <thread>
#include "controller.h"

class Room
{
public:
    explicit Room(std::shared_ptr<Controller> controller);
    ~Room() = default;
    void start();
    void stop();
private:
    std::shared_ptr<Controller> controller_;
    bool running_;
    bool cooling_;
    int temperature_; // in 0.1 degrees
    int temperature_delta_;  // in 0.1 degree
    std::thread cycle_thread_;
    void airco_monitor_(Airco::State old_state, Airco::State new_state);
    void cycle_();

    void init_();
};


#endif //AIRCO_ROOM_H
