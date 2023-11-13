cmake_minimum_required(VERSION 3.5)


# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include(GoogleTest) #needed for gtest_discover_tests

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()


set(SOURCES
    main.cpp
    TestSyntaxTree.cpp

)
add_executable(TestSyntaxTree ${SOURCES})

target_link_libraries(TestSyntaxTree GTest::gtest GTest::gtest_main)

gtest_discover_tests(TestSyntaxTree)




