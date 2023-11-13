cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Graphics)


set(SOURCES
    src/renderer.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3)
find_package(GLEW)

include_directories(
${OPENGL_INCLUDE_DIR}
${glfw_INCLUDE_DIRS}
${GLEW_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
${OPENGL_LIBRARIES}
${glfw_LIBRARIES}
${GLEW_LIBRARIES}
)




