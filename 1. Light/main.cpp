#include <iostream>
#include <memory>
#include "light.h"

int main()
{
    std::cout << "Testing Light class" << std::endl;

    std::cout << "Creating lights" << std::endl;
    std::shared_ptr<Light> green_light = std::make_shared<Light>();
    green_light->SetName("green");
    std::shared_ptr<Light> amber_light = std::make_shared<Light>("amber");
    std::shared_ptr<Light> red_light = std::make_shared<Light>("red", Light::State::On);
    std::cout << "Lights: " << *red_light << ", " << *amber_light << ", " << *green_light << std::endl;

    std::cout << "Setting red light off, and green light on" << std::endl;
    red_light->SetState(Light::State::Off);
    green_light->SetState(Light::State::On);
    std::cout << "Lights: " << *red_light << ", " << *amber_light << ", " << *green_light << std::endl;

    std::cout << "Setting green light off, and amber light flashing" << std::endl;
    green_light->SetState(Light::State::Off);
    amber_light->SetState(Light::State::Flashing);
    std::cout << "Lights: " << *red_light << ", " << *amber_light << ", " << *green_light << std::endl;
}
