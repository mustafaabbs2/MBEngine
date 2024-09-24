cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Graphics)

if(APPLE)
	set(HOOPS_COMPILE FALSE)
endif()

if(HOOPS_COMPILE)
	add_subdirectory(hoops)
endif()

set(SOURCES
    src/main.cpp
    src/Render.cpp
	src/ImguiUtils.cpp
	src/ShaderUtils.cpp
	src/WindowUtils.cpp
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



include_directories(
${OPENGL_INCLUDE_DIR}
${glfw_INCLUDE_DIRS}
${GLEW_INCLUDE_DIRS}
include/
)



add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME}
${OPENGL_LIBRARIES}
${glfw_LIBRARIES}
${GLEW_LIBRARIES}
)

#MarchingCubes...

set(MCUBE_SOURCES
    src/MarchingCubes.cpp
)

add_executable(MarchingCubes ${MCUBE_SOURCES})

target_link_libraries(MarchingCubes
${OPENGL_LIBRARIES}
${glfw_LIBRARIES}
${GLEW_LIBRARIES}
)

set(SNET_SOURCES
    src/SurfaceNets.c
)

add_executable(SurfaceNets ${SNET_SOURCES})
