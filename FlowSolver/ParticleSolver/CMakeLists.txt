cmake_minimum_required(VERSION 3.5)

project(ParticleSolver LANGUAGES CXX) 

message("Configuring ParticleSolver..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCES
    main.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} 
${CPP_SOURCES}
)


target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    # Find OpenMP package
    find_package(OpenMP REQUIRED)

    # Enable OpenMP
    if(OpenMP_CXX_FOUND)
        # Set OpenMP flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
        target_link_libraries(${PROJECT_NAME}  PUBLIC OpenMP::OpenMP_CXX)
    else()
        message(FATAL_ERROR "OpenMP not found. Please make sure to install it.")
    endif()
else() #for apple

    # Specify include directories
    include_directories(/opt/homebrew/opt/libomp/include)

    # Specify library directories
    link_directories(/opt/homebrew/opt/libomp/lib)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib")

    # Specify the OpenMP library 
    target_link_libraries(${PROJECT_NAME} PUBLIC omp)

    # Enable OpenMP for C++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fopenmp")

endif()


