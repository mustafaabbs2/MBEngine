
set(SOURCES
    src/headservice.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(client
    PRIVATE
    protolib
)

