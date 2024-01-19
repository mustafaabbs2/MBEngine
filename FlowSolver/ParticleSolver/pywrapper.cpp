#include "solver.h"
#include <iostream>
#include <pybind11/pybind11.h>


namespace py = pybind11;

//test
PYBIND11_MODULE(particle_module, m)
{
	m.def("hello_world", &hello_world);//just a test
}