
set(SOURCES
    src/headclient.cpp
)

add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
    protolib
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../protocol/protos)
