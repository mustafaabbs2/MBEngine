cmake_minimum_required(VERSION 3.5)

project(SyntaxTree LANGUAGES CXX) 

message("Configuring SyntaxTree..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
include/)



