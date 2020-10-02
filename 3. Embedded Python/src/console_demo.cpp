#include <string>

#include "airco.h"
#include "controller.h"
#include "thermostat.h"
#include "temperature.h"

#include "pybind11/embed.h"

namespace py = pybind11;
using namespace py::literals;

int main()
{
    py::scoped_interpreter guard{};

    auto airco_module = py::module::import("airco");

    auto controller = Controller();
    auto thermostat = Thermostat();
    auto airco = Airco(controller, thermostat);

    auto locals = py::dict(
            "airco"_a = py::cast(airco),
            "controller"_a = py::cast(controller),
            "thermostat"_a = py::cast(thermostat)
            );

    auto code_module = py::module::import("code");
    auto interact_func = code_module.attr("interact");
    interact_func(py::cast("Airco interactive shell"), nullptr, locals, py::cast("Bye now"));

    py::print("Verifying that C++ objects still exist");
    controller.signal(TemperatureSignal::TEMP_HIGH);
    py::print(thermostat.temperature(21.5));
    airco.start();
}
