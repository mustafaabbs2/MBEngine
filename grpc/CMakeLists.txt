cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(grpc-server)


set(SOURCES
    src/headservice.cpp
)

add_executable(grpc-server ${SOURCES})




