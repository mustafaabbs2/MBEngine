cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(Server)

message("Configuring Server..")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(renderer)
add_subdirectory(remoting)
add_subdirectory(webserver)
