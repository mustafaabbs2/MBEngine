cmake_minimum_required(VERSION 3.5)
project(Server)

message("Configuring Server..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/server.cpp
)

# Add executable target
add_executable(Server ${SOURCES})


# Add include directories
target_include_directories(Server PRIVATE 
include/)




