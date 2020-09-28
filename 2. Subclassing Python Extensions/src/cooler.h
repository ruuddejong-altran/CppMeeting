#ifndef AIRCO_COOLER_H
#define AIRCO_COOLER_H

#include <iostream>
#include <functional>

class Cooler
{
public:
    using CallbackFunctionType = std::function<void(bool)>;

    Cooler();
    virtual ~Cooler() = default;

    enum class State
    {
        Off, On
    };

    virtual void On();
    virtual void Off();
    [[nodiscard]] virtual State GetState() const;
    virtual void AddCallback(const CallbackFunctionType& func);

private:
    void ChangeState_(State new_state);

    State state_;
    std::vector<CallbackFunctionType> callbacks_;
};

std::string& ToString(Cooler::State state);
std::ostream& operator<<(std::ostream& ostream, Cooler::State state);

#endif //AIRCO_COOLER_H
