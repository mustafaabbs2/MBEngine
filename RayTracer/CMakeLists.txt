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

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})


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


#Make the optix stuff work

set(OPTIX_SOURCES
    src/Optix/main.cu
)


#make it find optix

set(OptiX_INSTALL_DIR "C:/ProgramData/NVIDIA Corporation/OptiX SDK 8.0.0")
list(APPEND CMAKE_MODULE_PATH "${OptiX_INSTALL_DIR}/SDK/CMake")
find_package(OptiX REQUIRED)

set_source_files_properties(${OPTIX_SOURCES} PROPERTIES LANGUAGE CUDA)

include_directories(${OptiX_INSTALL_DIR}/include)

add_executable(OptixRayTracer 
${OPTIX_SOURCES}
)


message("OptiX_INCLUDE is: ${OptiX_INCLUDE}")


#set_source_files_properties(${OPTIX_SOURCES} PROPERTIES CUDA_PTX_COMPILATION ON)
#set_source_files_properties(${OPTIX_SOURCES}  PROPERTIES COMPILE_FLAGS "--keep -rdc=true")


# Add include directories
target_include_directories(OptixRayTracer PRIVATE 
${PNG_INCLUDE_DIR}
${CUDA_INCLUDE_DIRS}
${OptiX_INCLUDE}
include/)

target_link_libraries(OptixRayTracer 
${CUDA_LIBRARIES})




