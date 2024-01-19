#include "solver.h"
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

//test

static void hello_world()
{
	std::cout << "Hello world\n";
}

static py::list get_array()
{
	std::vector<double> output(1, 100);
	py::list L;
	for(auto v : output)
		L.append(v);
	return L;
}

PYBIND11_MODULE(particle_module, m)
{
	m.def("hello_world", &hello_world);
	m.def("get_array", &get_array);
}
