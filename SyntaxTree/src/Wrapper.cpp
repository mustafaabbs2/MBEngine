// hello.cpp
#include <pybind11/pybind11.h>
#include <iostream>

void say_hello() {
    std::cout << "Hello, World!" << std::endl;
}

PYBIND11_MODULE(hello, m) {
    m.def("say_hello", &say_hello, "A function that prints 'Hello, World!'");
}
