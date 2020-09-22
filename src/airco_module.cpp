#include "pybind11/pybind11.h"
#include "pybind11/functional.h"

#include "airco.h"

namespace py = pybind11;

using namespace py::literals;


PYBIND11_MODULE(airco, m)
{
    m.doc() = "airco extension module";

    py::class_<Airco> Airco(m, "Airco");

    py::enum_<Airco::State>(Airco, "State")
            .value("Off", Airco::State::Off)
            .value("On", Airco::State::On);

    Airco.def(py::init<>())
            .def_property_readonly("state", &Airco::GetState, "The airco's state")
            .def("On", &Airco::On, "Turn the airco on")
            .def("Off", &Airco::Off, "Turn the airco off")
            .def("AddCallback", &Airco::AddCallback, "Add transition callback function f(old_state, new_state)");
}