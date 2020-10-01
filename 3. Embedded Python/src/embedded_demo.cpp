#include "airco.h"

#include "pybind11/embed.h"

namespace py = pybind11;
using namespace py::literals;


int main()
{
    py::scoped_interpreter guard{};

    py::print("importing pycontroller module");
    py::module pycontroller_module = py::module::import("pycontroller");

    py::print("getting PyCntroller class");
    py::object controller_class = pycontroller_module.attr("PyController");
    py::print("instantiating controller");
    py::object py_controller = controller_class();
    py::print("calling 'signal' on controller");
    py_controller.attr("signal")(TemperatureSignal::TEMP_HIGH);

    auto controller = py_controller.cast<Controller*>();
    auto thermostat = Thermostat();
    Airco airco = Airco(*controller, thermostat);

    auto cb = [](bool cooling)
    {
        if (cooling)
        {
            py::print("[Callback] Cooling down");
        }
        else
        {
            py::print("[Callback] Warming up");
        }
    };
    airco.add_callback(cb);
    airco.start();
    airco.temperature(20.5);
    airco.temperature(21.2);
    airco.temperature(20.6);
    airco.temperature(19.8);
    airco.temperature(20.4);
    airco.stop();
}
