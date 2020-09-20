#ifndef PYTHON_C_CPP_LIGHT_H
#define PYTHON_C_CPP_LIGHT_H

#include <iostream>

class Light
{
public:
    enum class State {Off, On, Flashing};

    explicit Light(const std::string& name="", State state=State::Off);
    ~Light();

    virtual std::string GetName() const;
    virtual void SetName(const std::string& name);

    virtual State GetState() const;
    virtual void SetState(State state);

private:
    std::string name_;
    State state_;
};

std::string& ToString(Light::State state);
std::ostream& operator<<(std::ostream& ostream, const Light& light);
std::ostream& operator<<(std::ostream& ostream, std::shared_ptr<Light> light);

#endif //PYTHON_C_CPP_LIGHT_H
