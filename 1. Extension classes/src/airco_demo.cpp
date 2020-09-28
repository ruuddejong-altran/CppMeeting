#include "airco.h"

using namespace std::chrono_literals;

int main()
{
    std::cout << "Testing Airco class" << std::endl;

    auto callback = [](bool cooler_is_running) {
        std::cout << "[Callback] Cooler is" << (cooler_is_running ? "" : " not") << " running" << std::endl;
    };

    std::cout << "Creating airco without cooler and controller" << std::endl;
    auto airco = Airco();
    std::cout << "Trying to add callback function (should give error message)" << std::endl;
    airco.AddCallback(callback);
    std::cout << "Trying to start airco (should give error message)" << std::endl;
    airco.Start();
    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);

    std::cout << "Creating controller" << std::endl;
    auto ctrl = std::make_shared<Controller>();
    std::cout << "Adding controller to airco" << std::endl;
    airco.SetController(ctrl);
    std::cout << "Trying to add callback function (should give error message)" << std::endl;
    airco.AddCallback(callback);
    std::cout << "Trying to start airco (should give error message)" << std::endl;
    airco.Start();
    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);

    std::cout << "Creating cooler" << std::endl;
    auto cooler = std::make_shared<Cooler>();
    std::cout << "Adding cooler to airco" << std::endl;
    airco.SetCooler(cooler);
    std::cout << "Trying to add callback function" << std::endl;
    airco.AddCallback(callback);
    std::cout << "Trying to start airco (should be successful)" << std::endl;
    airco.Start();
    std::cout << "Trying temperature values" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);
    airco.Temperature(20.6);
    airco.Temperature(19.9);
    std::cout << "Stopping airco" << std::endl;
    airco.Stop();
    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);

    return 0;
}

