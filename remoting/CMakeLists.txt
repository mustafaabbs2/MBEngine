cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(remoting)


set(SOURCES
    src/headservice.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})


