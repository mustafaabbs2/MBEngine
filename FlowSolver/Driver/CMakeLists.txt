cmake_minimum_required(VERSION 3.5)

project(Driver LANGUAGES CXX) 

message("Configuring FlowSolver..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCES
    driver.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} 
${CPP_SOURCES}
)

message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)





