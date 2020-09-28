#include "pybind11/pybind11.h"
#include "pybind11/functional.h"

#include "cooler.h"
#include "controller.h"
#include "airco.h"

namespace py = pybind11;

using namespace py::literals;


PYBIND11_MODULE(airco, m)
{
    m.doc() = "Airco extension module";

    py::class_<Cooler, std::shared_ptr<Cooler>> py_cooler(m, "Cooler");

    py::enum_<Cooler::State>(py_cooler, "State")
            .value("OFF", Cooler::State::Off)
            .value("ON", Cooler::State::On);

    py_cooler.def(py::init<>())
            .def_property_readonly("state", &Cooler::GetState, "The cooler's state")
            .def("on", &Cooler::On, "Turn the cooler on")
            .def("off", &Cooler::Off, "Turn the cooler off")
            .def("add_callback", &Cooler::AddCallback, "Add transition callback function f(cooler_running)");

    py::class_<Controller, std::shared_ptr<Controller>> py_controller(m, "Controller");

    py::enum_<Controller::Event>(py_controller, "Event")
            .value("TEMP_HIGH", Controller::Event::TEMP_HIGH)
            .value("TEMP_OK", Controller::Event::TEMP_OK)
            .value("TEMP_LOW", Controller::Event::TEMP_LOW);

    py_controller.def(py::init<>())
            .def(py::init<std::shared_ptr<Cooler>>())
            .def_property("cooler", &Controller::GetCooler, &Controller::SetCooler)
            .def("signal", &Controller::Signal);

    py::class_<Airco>(m, "Airco")
            .def(py::init<>())
            .def(py::init<double>())
            .def(py::init<double, double>())
            .def(py::init<double, double, std::shared_ptr<Controller>>())
            .def(py::init<double, double, std::shared_ptr<Controller>, std::shared_ptr<Cooler>>())
            .def("start", &Airco::Start)
            .def("stop", &Airco::Stop)
            .def("temperature", &Airco::Temperature)
            .def_property("controller", &Airco::GetController, &Airco::SetController)
            .def_property("cooler", &Airco::GetCooler, &Airco::SetCooler)
            .def_property("temperature_range", &Airco::GetTemperatureRange, &Airco::SetTemperatureRange)
            .def("add_callback", &Airco::AddCallback);
}
