#include "pybind11/embed.h"

#include "airco.h"

namespace py = pybind11;
using namespace std::chrono_literals;
using namespace py::literals;

int main()
{
    py::scoped_interpreter guard{};
    py::module pycontroller_module = py::module::import("pycontroller");
    py::object pycontroller_class = pycontroller_module.attr("PyController");
    py::object pycontroller_object = pycontroller_class();

    py::print("Testing Airco class");

    auto callback = [](bool cooler_is_running) {
        py::print("[Callback] Cooler is ", (cooler_is_running ? "" : "not "), "running", "sep"_a="");
    };

    auto airco = Airco();

    py::print("Adding cooler to airco");
    airco.SetCooler(std::make_shared<Cooler>());
    py::print("Adding PyController object to airco");
    airco.SetController(py::handle(pycontroller_object).cast<std::shared_ptr<Controller>>());
    std::cout << "Adding callback function" << std::endl;
    airco.AddCallback(callback);
    std::cout << "Trying to start airco (should be successful)" << std::endl;
    airco.Start();
    std::cout << "Trying temperature values" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);
    airco.Temperature(20.6);
    airco.Temperature(19.9);
    std::cout << "Stopping airco" << std::endl;
    airco.Stop();
    std::cout << "Trying temperature values (should not give any result)" << std::endl;
    airco.Temperature(19.8);
    airco.Temperature(20.5);
    airco.Temperature(21.2);

    return 0;
}

