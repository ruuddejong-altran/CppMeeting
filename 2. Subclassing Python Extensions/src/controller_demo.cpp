#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "controller.h"

int main()
{
    std::cout << "Testing Controller class" << std::endl;

    auto cb = [](bool value)
    {
        std::cout << "[Callback] Called with " << value << std::endl;
    };

    std::cout << "Creating controller" << std::endl;
    Controller controller = Controller();

    std::cout << "Adding callback function" << std::endl;
    controller.add_callback(cb);

    std::cout << "Trying temperature signal" << std::endl;
    controller.signal(TemperatureSignal::TEMP_LOW);
    controller.signal(TemperatureSignal::TEMP_OK);
    controller.signal(TemperatureSignal::TEMP_HIGH);
    controller.signal(TemperatureSignal::TEMP_OK);

    return 0;
}

