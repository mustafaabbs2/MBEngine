cmake_minimum_required(VERSION 3.5)

project(SyntaxTree LANGUAGES CXX) 

message("Configuring SyntaxTree..")

find_package(Python REQUIRED)
find_package(pybind11 REQUIRED)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Wrapper.cpp

)
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
include/
${pybind11_INCLUDE_DIRS}
${Python3_INCLUDE_DIRS}
)


target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARY_RELEASE})




