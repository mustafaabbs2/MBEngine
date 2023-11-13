cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(chatServer)
message("Configuring client..")


set(SOURCES
    src/server.cpp
)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)

include_directories(
${Boost_INCLUDE_DIRS}
)

#needed for compiling on windows
add_definitions(-DBOOST_DATE_TIME_NO_LIB)
add_definitions(-DBOOST_REGEX_NO_LIB)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PUBLIC
${Boost_LIB_DIRS}
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})




