cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Graphics)


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





#Test for a HOOPS viewer

set(HOOPS_COMPILE TRUE)

if(HOOPS_COMPILE)

	set(HOOPS_DEPENDENCIES_PATH "D:\\Mustafa\\hoops_3df2720_nt_x64_v141\\HOOPS_3DF_2720\\Dev_Tools")

	set(HOOPS_SOURCES
		src/HoopsRenderer.cpp
	)

	include_directories(
		${HOOPS_DEPENDENCIES_PATH}/base_stream/source
		${HOOPS_DEPENDENCIES_PATH}/base_stream/source/stream_common
		${HOOPS_DEPENDENCIES_PATH}/hoops_3dgs/source
		${HOOPS_DEPENDENCIES_PATH}/hoops_mvo/source
		${HOOPS_DEPENDENCIES_PATH}/hoops_stream/source
		${HOOPS_DEPENDENCIES_PATH}/utility/source
	)


	add_executable(HoopsRenderer ${HOOPS_SOURCES})



	target_link_libraries(HoopsRenderer
		${HOOPS_DEPENDENCIES_PATH}/hoops_3dgs/lib/nt_x64_v141/hoops.lib
		${HOOPS_DEPENDENCIES_PATH}/hoops_mvo/lib/nt_x64_v141/hoops_mvo.lib
		${HOOPS_DEPENDENCIES_PATH}/hoops_stream/lib/nt_x64_v141/hoops_stream.lib
		${HOOPS_DEPENDENCIES_PATH}/utility/lib/nt_x64_v141/hoops_utilsstatd_mt.lib
	)

endif()



