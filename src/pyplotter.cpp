#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "graph.hpp"
#include "plotter.hpp"
#include "graphline.hpp"

PYBIND11_MODULE(PyPlotter, m){
  py::class_<Plotter>(m, "Plotter")
    .def(py::init<const char*, const int, const int>())
    .def("main_loop", &Plotter::MainLoop);

  py::class_<Graph>(m, "Graph")
    .def(py::init<const int, const int, const int, const int>())
    .def("draw", &Graph::Draw)
    .def("draw_line", &Graph::DrawLine);

  py::class_<GraphLine>(m, "Line")
    .def(py::init())
    .def("calculate", &GraphLine::Calculate)
    .def("plot", &GraphLine::Plot);

}
