#include <iostream>
#include <memory>

#include "cooler.h"

int main()
{
    std::cout << "Testing Cooler class" << std::endl;

    std::cout << "Creating Cooler" << std::endl;
    std::shared_ptr<Cooler> cooler = std::make_shared<Cooler>();
    std::cout << "Initial cooler state: " << cooler->GetState() << std::endl;

    std::cout << "Registering callback function" << std::endl;
    auto f = [](bool cooler_is_running) {
        std::cout << "[Callback] Cooler is" << (cooler_is_running ? "" : " not") << " running" << std::endl;
    };
    cooler->AddCallback(f);
    std::cout << "Switching cooler on" << std::endl;
    cooler->On();
    std::cout << "Switching cooler off" << std::endl;
    cooler->Off();
    std::cout << "No callback for repeatedly setting the same state" << std::endl;
    cooler->Off();
    return 0;
}
