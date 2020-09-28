#include <memory>

#include "cooler.h"
#include "controller.h"
#include "airco.h"
#include "room.h"

#include "pybind11/embed.h"

namespace py = pybind11;
using namespace py::literals;

int main()
{
    py::scoped_interpreter guard{};

    py::print("importing airco");
    py::module airco = py::module::import("airco");
    py::print("getting cooler type");
    py::object cooler_type = airco.attr("Cooler");
    py::print("instantiating cooler");
    py::object cooler = cooler_type();
    auto on_func = cooler_type.attr("on");
    if (on_func)
    {
        on_func(cooler);
    }
    else
    {
        py::print("on_func is null");
    }
    py::print("So far, so good");
}
