cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(MBEngine)

message("Configuring MBEngine..")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRPC_WORKING TRUE)

set(CUDA_ENABLED TRUE)
if(APPLE)
    set(CUDA_ENABLED FALSE)
endif()
set(PYTHON_ENABLED FALSE)



if(GRPC_WORKING) #issue with the grpc version --> can be resolved by using >VS2019 14.28 and above for windows
add_subdirectory(RemotingService)
endif()
add_subdirectory(Graphics)
add_subdirectory(ChatService)
if(CUDA_ENABLED)
add_subdirectory(RayTracer)
endif()
add_subdirectory(FlowSolver)
if(PYTHON_ENABLED)
add_subdirectory(SyntaxTree)
endif()
add_subdirectory(Tests)


