
set(SOURCES
    src/headservice.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PRIVATE
    protolib
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../protocol/protos)


find_package(RPC REQUIRED)
target_link_libraries(server PRIVATE RPC::RPC)



#Now, the onc server


#set(ONC_SOURCES
#    src/headservice_onc.cpp
#)

#add_executable(onc_server ${ONC_SOURCES})




