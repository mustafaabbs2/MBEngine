cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(Server)

message("Configuring Server..")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRPC_WORKING FALSE)
set(CUDA_ENABLED FALSE)


if(GRPC_WORKING) #issue with the grpc version --> can be resolved by using >VS2019 14.28 and above for windows
add_subdirectory(RemotingService)
endif()
add_subdirectory(Graphics)
add_subdirectory(ChatService)
if(CUDA_ENABLED)
add_subdirectory(RayTracer)
endif()
add_subdirectory(FlowSolver)
add_subdirectory(SyntaxTree)
add_subdirectory(Tests)


