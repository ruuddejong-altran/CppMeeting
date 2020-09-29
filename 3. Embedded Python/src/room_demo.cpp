#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "controller.h"
#include "thermostat.h"
#include "airco.h"
#include "room.h"


int main()
{
    std::cout << "Testing Airco class" << std::endl;

    auto callback = [](bool cooler_is_running)
    {
        std::cout << "[Callback] Cooler is" << (cooler_is_running ? "" : " not") << " running" << std::endl;
    };

    auto controller = Controller();
    auto thermostat = Thermostat();
    auto airco = Airco(controller, thermostat);
    airco.add_callback(callback);

    Room room(airco);
    room.Start();
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20s);
    }
    room.Stop();
}