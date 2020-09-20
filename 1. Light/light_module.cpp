#include "pybind11/pybind11.h"
#include "pybind11/functional.h"

#include "light.h"

namespace py = pybind11;

using namespace py::literals;


PYBIND11_MODULE(light, m)
{
    m.doc() = "light extension module";

    py::class_<Light> Light(m, "Light");

    py::enum_<Light::State>(Light, "State")
            .value("Off", Light::State::Off)
            .value("On", Light::State::On)
            .value("Flashing", Light::State::Flashing)
            .export_values();

    Light.def(py::init<const std::string&, Light::State>(), "name"_a = "", "state"_a = Light::State::Off)
            .def_property("name", &Light::GetName, &Light::SetName, "The light's name")
            .def_property("state", &Light::GetState, &Light::SetState, "The light's state");

}
