#include <iostream>
#include "airco.h"

int main()
{
    std::cout << "Testing Airco class" << std::endl;

    auto callback = [](bool cooler_is_running) {
        std::cout << "[Callback] Airco is" << (cooler_is_running ? "" : " not") << " cooling" << std::endl;
    };

    std::cout << "Creating thermostat" << std::endl;
    auto thermostat = Thermostat();

    std::cout << "Creating controller" << std::endl;
    auto controller = Controller();

    std::cout << "Creating airco" << std::endl;
    auto airco = Airco(controller, thermostat);

    std::cout << "Adding callback function" << std::endl;
    airco.add_callback(callback);

    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.temperature(19.8);
    airco.temperature(20.5);
    airco.temperature(21.2);

    std::cout << "Starting airco" << std::endl;
    airco.start();

    std::cout << "Trying temperature values (should give result)" << std::endl;
    airco.temperature(19.8);
    airco.temperature(20.5);
    airco.temperature(21.2);

    std::cout << "Stopping airco" << std::endl;
    airco.stop();

    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.temperature(19.8);
    airco.temperature(20.5);
    airco.temperature(21.2);

    return 0;
}

