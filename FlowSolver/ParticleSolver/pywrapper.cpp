#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void hello_world()
{
	std::cout << "Hello world\n";
}

//test
PYBIND11_MODULE(particle_module, m)
{
	m.def("hello_world", &hello_world);
}