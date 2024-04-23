
set(SOURCES
    src/headservice.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PRIVATE
    protolib
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../protocol/protos)



if(0)
#Now, the onc server
set(RPC_INCLUDE_DIR "D:/Mustafa/MBEngine/oncrpc")
set(RPC_LIBRARY_DIR "D:/Mustafa/MBEngine/oncrpc/Debug")
include_directories(${RPC_INCLUDE_DIR})
link_directories(${RPC_LIBRARY_DIR})


set(ONC_SOURCES
    src/headservice_onc.c
)

add_executable(onc_server ${ONC_SOURCES})

target_link_libraries(onc_server
    PRIVATE
    oncrpc
)
endif()



