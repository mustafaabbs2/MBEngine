cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(webserver)
message("Configuring webserver..")

#comment this out for now
if(FALSE) 
set(VCPKG_ROOT "D:/Mustafa/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

Message(${CMAKE_TOOLCHAIN_FILE})


set(SOURCES
    src/server.cpp
)

set(Boost_USE_STATIC_LIBS ON)

# Find and link Boost
find_package(Boost 1.82.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    # Add executable target
    #target_include_directories(Server PRIVATE include/)
    add_executable(Server ${SOURCES})
    #target_link_libraries(Server PRIVATE ${Boost_LIBRARIES})
endif()


endif()




