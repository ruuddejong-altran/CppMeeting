#ifndef AIRCO_AIRCO_H
#define AIRCO_AIRCO_H

#include <condition_variable>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>

#include "controller.h"
#include "cooler.h"

class Airco
{
public:
    explicit Airco(double low_temperature = 20.0, double high_temperature = 21.0,
                   std::shared_ptr<Controller> controller = nullptr, std::shared_ptr<Cooler> cooler = nullptr);

    virtual ~Airco() = default;

    virtual void Start();
    virtual void Stop();
    virtual void Temperature(double temperature);
    virtual void SetController(std::shared_ptr<Controller> controller);
    virtual void SetCooler(std::shared_ptr<Cooler> cooler);
    virtual std::shared_ptr<Controller> GetController();
    virtual std::shared_ptr<Cooler> GetCooler();
    virtual void SetTemperatureRange(double low_temp, double high_temp);
    virtual std::pair<double, double> GetTemperatureRange();
    virtual void AddCallback(const Cooler::CallbackFunctionType& callback);

private:
    std::shared_ptr<Controller> controller_;
    std::shared_ptr<Cooler> cooler_;
    bool running_;
    double temperature_high_;
    double temperature_low_;
};


#endif //AIRCO_AIRCO_H
