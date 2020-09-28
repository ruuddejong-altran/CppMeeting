#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "cooler.h"
#include "controller.h"

int main()
{
    std::cout << "Testing Controller class" << std::endl;

    std::cout << "Creating controller without cooler" << std::endl;
    auto ctrl = std::make_shared<Controller>();
    std::cout << "Trying temperature signal" << std::endl;
    ctrl->Signal(Controller::Event::TEMP_LOW);
    ctrl->Signal(Controller::Event::TEMP_OK);
    ctrl->Signal(Controller::Event::TEMP_HIGH);
    ctrl->Signal(Controller::Event::TEMP_OK);

    std::cout << "Adding cooler to controller" << std::endl;
    auto cooler = std::make_shared<Cooler>();
    std::cout << "Cooler state is: " << cooler->GetState() << std::endl;
    ctrl->SetCooler(cooler);
    std::cout << "Trying temperature signal" << std::endl;
    ctrl->Signal(Controller::Event::TEMP_LOW);
    ctrl->Signal(Controller::Event::TEMP_OK);
    ctrl->Signal(Controller::Event::TEMP_HIGH);
    ctrl->Signal(Controller::Event::TEMP_OK);

    std::cout << "Creating controller with existing cooler" << std::endl;
    std::cout << "Cooler state is: " << cooler->GetState() << std::endl;
    ctrl = std::make_shared<Controller>(cooler);
    std::cout << "Trying temperature signal" << std::endl;
    ctrl->Signal(Controller::Event::TEMP_LOW);
    ctrl->Signal(Controller::Event::TEMP_OK);
    ctrl->Signal(Controller::Event::TEMP_HIGH);
    ctrl->Signal(Controller::Event::TEMP_OK);

    return 0;
}

