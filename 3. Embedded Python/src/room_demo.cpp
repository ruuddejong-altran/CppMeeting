#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "cooler.h"
#include "controller.h"
#include "airco.h"
#include "room.h"


int main()
{
    std::cout << "Testing Airco class" << std::endl;

    auto callback = [](bool cooler_is_running)
    {
        std::cout << "[Callback] Cooler is" << (cooler_is_running ? "" : " not") << " running" << std::endl;
    };

    std::shared_ptr<Cooler> cooler = std::make_shared<Cooler>();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>();
    std::shared_ptr<Airco> airco = std::make_shared<Airco>();
    airco->SetController(controller);
    airco->SetCooler(cooler);
    airco->AddCallback(callback);

    Room room(airco);
    room.Start();
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20s);
    }
    room.Stop();
}