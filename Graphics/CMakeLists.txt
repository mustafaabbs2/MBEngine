cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Graphics)


set(SOURCES
    src/main.cpp
    src/Render.cpp
)

set(IMGUI_SOURCES
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
    src/imgui/imgui.cpp
	src/imgui/imgui_demo.cpp
	src/imgui/imgui_draw.cpp
	src/imgui/imgui_impl_glfw.cpp
	src/imgui/imgui_impl_opengl3.cpp
	src/imgui/imgui_tables.cpp
	src/imgui/imgui_widgets.cpp
)


find_package(OpenGL REQUIRED)
find_package(glfw3)
find_package(GLEW)
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(imgui REQUIRED) #do I need this if everything is part of the project anyway?


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include_directories(
${OPENGL_INCLUDE_DIR}
${glfw_INCLUDE_DIRS}
${GLEW_INCLUDE_DIRS}
${Qt5Widgets_INCLUDE_DIRS}
include/
src/
)

add_executable(${PROJECT_NAME} ${SOURCES})

#add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})


target_link_libraries(${PROJECT_NAME}
${OPENGL_LIBRARIES}
${glfw_LIBRARIES}
${GLEW_LIBRARIES}
Qt5::Widgets
imgui::imgui
)




