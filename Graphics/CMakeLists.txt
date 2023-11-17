cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Graphics)


set(SOURCES
    src/renderer.cpp
)

set(UI_SOURCES
    src/QT/QtGUI.cpp
)


find_package(OpenGL REQUIRED)
find_package(glfw3)
find_package(GLEW)
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include_directories(
${OPENGL_INCLUDE_DIR}
${glfw_INCLUDE_DIRS}
${GLEW_INCLUDE_DIRS}
${Qt5Widgets_INCLUDE_DIRS}
include/
)

add_executable(${PROJECT_NAME} ${SOURCES} ${UI_SOURCES})

target_link_libraries(${PROJECT_NAME}
${OPENGL_LIBRARIES}
${glfw_LIBRARIES}
${GLEW_LIBRARIES}
 Qt5::Widgets
)




