
set(SOURCES
    src/headclient.cpp
)

add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
    protolib
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../protocol/protos)


if(0)
#Now, the onc client
set(RPC_INCLUDE_DIR "D:/Mustafa/MBEngine/oncrpc")
set(RPC_LIBRARY_DIR "D:/Mustafa/MBEngine/oncrpc/Debug")
include_directories(${RPC_INCLUDE_DIR})
link_directories(${RPC_LIBRARY_DIR})


set(ONC_SOURCES
    src/headclient_onc.c
)

add_executable(onc_client ${ONC_SOURCES})

target_link_libraries(onc_client
    PRIVATE
    oncrpc
)
endif()



