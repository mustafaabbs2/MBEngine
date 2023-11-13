cmake_minimum_required(VERSION 3.5)

project(FlowSolver LANGUAGES CXX) 

message("Configuring FlowSolver..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCES
    src/main.cpp
)

# Add executable target
add_executable(FlowSolver 
${CPP_SOURCES}
)

# Add include directories
target_include_directories(FlowSolver PRIVATE 
include/)



