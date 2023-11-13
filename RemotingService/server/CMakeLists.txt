
set(SOURCES
    src/headservice.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PRIVATE
    protolib
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../protocol/protos)


