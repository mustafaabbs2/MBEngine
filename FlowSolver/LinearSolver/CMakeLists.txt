cmake_minimum_required(VERSION 3.5)

project(LinearSolver LANGUAGES CXX) 

message("Configuring LinearSolver..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

# Find OpenMP package
find_package(OpenMP REQUIRED)


set(CPP_SOURCES
    Jacobi.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} 
${CPP_SOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable OpenMP
if(OpenMP_CXX_FOUND)
    # Set OpenMP flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    include_directories("${OpenMP_CXX_INCLUDE_DIRS}")
    target_link_libraries(${PROJECT_NAME}  PUBLIC OpenMP::OpenMP_CXX)
else()
    message(FATAL_ERROR "OpenMP not found. Please make sure to install it.")
endif()


