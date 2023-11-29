cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(HoopsRenderer)


set(HOOPS_DEPENDENCIES_PATH "D:\\Mustafa\\hoops_3df2720_nt_x64_v141\\HOOPS_3DF_2720\\Dev_Tools")

set(HOOPS_SOURCES
	HoopsRenderer.cpp
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




