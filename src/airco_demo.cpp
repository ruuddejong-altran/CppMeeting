#include <iostream>
#include <memory>
#include "airco.h"

int main()
{
    std::cout << "Testing Airco class" << std::endl;

    std::cout << "Creating Airco" << std::endl;
    std::shared_ptr<Airco> airco = std::make_shared<Airco>();
    std::cout << "Initial airco state: " << airco->GetState() << std::endl;

    std::cout << "Registering callback function" << std::endl;
    auto f = [](Airco::State old_state, Airco::State new_state) {
        std::cout << "Transitioning from " << old_state << " to " << new_state << std::endl;
    };
    airco->AddCallback(f);
    std::cout << "Switching airco on" << std::endl;
    airco->On();
    std::cout << "Switching airco off" << std::endl;
    airco->Off();
    std::cout << "No callback for repeatedly setting the same state" << std::endl;
    airco->Off();
}
