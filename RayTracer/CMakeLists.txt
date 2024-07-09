cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(RayTracer LANGUAGES CXX CUDA) #this will automatically compile CUDA sources with nvcc

message("Configuring RayTracer..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCES
    src/main.cpp
    src/Core/Octree.cpp
    src/Core/Color.cpp
    src/Core/HitterList.cpp
    src/Core/Material.cpp
    src/Core/Metal.cpp
    src/Core/Lambertian.cpp
    src/Core/Ray.cpp
    src/Core/Vec3.cpp
    src/Core/Sphere.cpp
    src/Core/Camera.cpp
    src/Core/ThreadPool.cpp
    src/Writers/PPMWriter.cpp
    src/Writers/PNGWriter.cpp
    src/Utils/Utils.cpp
    src/Utils/Logger.cpp
)

set(CUDA_SOURCES
    src/Cuda/RayKernel.cxx
)



set_source_files_properties(${CUDA_SOURCES} PROPERTIES LANGUAGE CUDA)


# Add executable target
add_executable(RayTracer 
${CPP_SOURCES}
${CUDA_SOURCES}
)

find_package(glfw3)


find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

#note: find package for CUDA is probably not required anymore
#find_package(CUDA 11.6 REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

# Print the CMAKE_CUDA_COMPILER variable
message(STATUS "CMAKE_CUDA_COMPILER: ${CMAKE_CUDA_COMPILER}")

# Print the CUDA_TOOLKIT_ROOT_DIR variable
message(STATUS "CUDA_TOOLKIT_ROOT_DIR: ${CUDA_TOOLKIT_ROOT_DIR}")

#forcing it for now
set(CMAKE_CUDA_COMPILER "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.6/bin/nvcc.exe")


set(CMAKE_CUDA_RUNTIME_LIBRARY Static)
	

if(MSVC)
	set(CUDA_LIBRARIES cudart_static cublas cuda cusparse)
else()
	find_library(CUDA_RT cudart PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
	find_library(CUDA_BLAS cublas PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
	find_library(CUDA_CUDA cuda PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
	find_library(CUDA_CUSPARSE cusparse PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
	set(CUDA_LIBRARIES ${CUDA_CUSPARSE} ${CUDA_RT} ${CUDA_BLAS} ${CUDA_CUDA} )
endif()
	
set(CMAKE_CUDA_FLAGS "-std c++17 ${CMAKE_CUDA_FLAGS}")


# Add include directories
target_include_directories(RayTracer PRIVATE 
${PNG_INCLUDE_DIR}
${CUDA_INCLUDE_DIRS}
include/)

target_link_libraries(RayTracer 
${CUDA_LIBRARIES}
PNG::PNG)

##The Optix Project...............................................

#Make the optix stuff work

set(OPTIX_SOURCES
    src/Optix/main.cu
)

set(SHADER_SOURCES
    src/Optix/optixTriangleKernel.cu
)


#make it find optix

set(OptiX_INSTALL_DIR "C:/ProgramData/NVIDIA Corporation/OptiX SDK 8.0.0")
list(APPEND CMAKE_MODULE_PATH "${OptiX_INSTALL_DIR}/SDK/CMake")
find_package(OptiX REQUIRED)

set_source_files_properties(${OPTIX_SOURCES} PROPERTIES LANGUAGE CUDA)

include_directories(
${OptiX_INSTALL_DIR}/include
${glfw_INCLUDE_DIRS}
)

add_executable(OptixRayTracer 
${OPTIX_SOURCES}
)

message("OptiX_INCLUDE is: ${OptiX_INCLUDE}")

# Define the PTX output files

set(PTX_FILES)
foreach(SHADER_SOURCE ${SHADER_SOURCES})
    get_filename_component(FILE_NAME ${SHADER_SOURCE} NAME_WE)
    list(APPEND PTX_FILES "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.ptx") #note, it needs to be in the bin/ folder so the executable can find it
endforeach()

set_source_files_properties(${SHADER_SOURCES} PROPERTIES CUDA_PTX_COMPILATION ON)
set_source_files_properties(${SHADER_SOURCES}  PROPERTIES COMPILE_FLAGS "--keep -rdc=true")

#Add custom commands to compile the shader sources to PTX

foreach(SHADER_SOURCE ${SHADER_SOURCES})
    message("Compiling shader source: ${SHADER_SOURCE}")

    get_filename_component(FILE_NAME ${SHADER_SOURCE} NAME_WE)
    set(PTX_FILE "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.ptx")
    set(SHADER_SOURCE "${CMAKE_SOURCE_DIR}/RayTracer/src/Optix/${FILE_NAME}.cu")
    message(${CMAKE_CUDA_COMPILER})
    
    add_custom_command(
        OUTPUT ${PTX_FILE}
        COMMAND ${CMAKE_CUDA_COMPILER} 
                -I${OptiX_INCLUDE}
                 ${SHADER_SOURCE} -ptx 
                 -o ${PTX_FILE}
                -lcudadevrt
        DEPENDS ${SHADER_SOURCE}
        COMMENT "Compiling ${SHADER_SOURCE} to ${PTX_FILE}"
    )
endforeach()

# Add custom target for PTX files
add_custom_target(CompileShaders ALL DEPENDS ${PTX_FILES})

# Ensure the PTX files are compiled before the main executable
add_dependencies(OptixRayTracer CompileShaders)


# Add include directories
target_include_directories(OptixRayTracer PRIVATE 
${PNG_INCLUDE_DIR}
${CUDA_INCLUDE_DIRS}
${OptiX_INCLUDE}
include/)

target_link_libraries(OptixRayTracer 
${CUDA_LIBRARIES}
${glfw_LIBRARIES}
)


##The OSPray Project...............................................

# Set the path to OSPray's cmake config file
set(OSPRAY_DIR "C:/Program Files/Intel/OSPRay v3/lib/cmake/ospray-3.1.0" CACHE PATH "Path to OSPray config")

# Use find_package to locate OSPray
find_package(ospray 3.1.0 REQUIRED CONFIG PATHS ${OSPRAY_DIR})

include_directories(
${glfw_INCLUDE_DIRS}
)


set(OSPRAY_SOURCES
    src/OSPRay/main.cpp
)

# Set the path to OSPRay's bin directory
set(OSPRAY_BIN_DIR "C:/Program Files/Intel/OSPRay v3/bin" CACHE PATH "Path to OSPRay bin directory")

add_executable(OSPRayTracer 
${OSPRAY_SOURCES}
)

# Add the bin directory to the PATH environment variable for the executable
if(WIN32)
    set_target_properties(OSPRayTracer PROPERTIES
        VS_DEBUGGER_ENVIRONMENT "PATH=${OSPRAY_BIN_DIR};$ENV{PATH}"
    )
endif()


target_link_libraries(OSPRayTracer ospray::ospray ${glfw_LIBRARIES})


