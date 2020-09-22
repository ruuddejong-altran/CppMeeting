#ifndef PYTHON_C_CPP_AIRCO_H
#define PYTHON_C_CPP_AIRCO_H

#include <iostream>
#include <functional>

class Airco
{
public:
    Airco();
    ~Airco() = default;

    enum class State {Off, On};

    void On();
    void Off();
    [[nodiscard]] State GetState() const;

    using CallbackFunctionType = std::function<void(State, State)>;
    void AddCallback(const CallbackFunctionType& func);

private:
    void ChangeState_(State new_state);
    State state_;
    std::vector<CallbackFunctionType> transition_callbacks_;
};

std::string& ToString(Airco::State state);
std::ostream& operator<<(std::ostream& ostream, Airco::State state);

#endif //PYTHON_C_CPP_AIRCO_H
