cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(Server)

message("Configuring Server..")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_WORKING TRUE)
set(GRPC_WORKING TRUE)


add_subdirectory(renderer)
if (${GRPC_WORKING})
add_subdirectory(remoting)
endif()
if (${BOOST_WORKING})
    add_subdirectory(asioChatBot)
endif()