cmake_minimum_required(VERSION 3.5)

project(BenchmarkSyntaxTree)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)

set(SOURCES
    BenchmarkSyntaxTree.cpp

)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} benchmark::benchmark)





