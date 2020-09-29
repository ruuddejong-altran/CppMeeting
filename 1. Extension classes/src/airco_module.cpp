#include "pybind11/pybind11.h"
#include "pybind11/functional.h"

#include "temperature.h"
#include "thermostat.h"
#include "controller.h"
#include "airco.h"

namespace py = pybind11;

using namespace py::literals;


PYBIND11_MODULE(airco, m)
{
    m.doc() = "Airco extension module";

    py::enum_<TemperatureSignal>(m, "Temperature")
            .value("TEMP_HIGH", TemperatureSignal::TEMP_HIGH)
            .value("TEMP_OK", TemperatureSignal::TEMP_OK)
            .value("TEMP_LOW", TemperatureSignal::TEMP_LOW);

    py::class_<Thermostat>(m, "Thermostat")
            .def(py::init<>())
            .def(py::init<double>())
            .def(py::init<double, double>())
            .def_property("temperature_range", &Thermostat::get_temperature_range, &Thermostat::set_temperature_range)
            .def("temperature", &Thermostat::temperature);

    py::class_<Controller>(m, "Controller")
            .def(py::init<>())
            .def("add_callback", &Controller::add_callback)
            .def("signal", &Controller::signal);

    py::class_<Airco>(m, "Airco")
            .def(py::init<Controller&, Thermostat&>())
            .def("start", &Airco::start)
            .def("stop", &Airco::stop)
            .def("temperature", &Airco::temperature)
            .def_property("temperature_range", &Airco::get_temperature_range, &Airco::set_temperature_range)
            .def("add_callback", &Airco::add_callback);
}
