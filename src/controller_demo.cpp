#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "airco.h"
#include "controller.h"
#include "room.h"

int main()
{
    std::cout << "Testing Controller class" << std::endl;

    std::cout << "Creating Airco" << std::endl;
    std::shared_ptr<Airco> airco = std::make_shared<Airco>();

    std::cout << "Creating Controller" << std::endl;
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(airco);

    std::cout << "Creating Room" << std::endl;
    std::shared_ptr<Room> room = std::make_shared<Room>(controller);

    std::cout << "Starting room cycle for 30 seconds" << std::endl;
    room->start();
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(30s);
    }
    room->stop();
}

