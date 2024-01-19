cmake_minimum_required(VERSION 3.5)

project(SyntaxTree LANGUAGES CXX) 

message("Configuring SyntaxTree..")

find_package(pybind11 REQUIRED)
find_package(Python COMPONENTS Interpreter Development)

message("Python_FOUND:${Python_FOUND}")
message("Python_VERSION:${Python_VERSION}")
message("Python_Development_FOUND:${Python_Development_FOUND}")
message("Python_LIBRARIES:${Python_LIBRARIES}")


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

target_link_libraries(${PROJECT_NAME} PUBLIC ${Python_LIBRARIES})





