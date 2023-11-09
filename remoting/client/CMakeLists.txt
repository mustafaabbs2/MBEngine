
set(SOURCES
    src/headclient.cpp
)

add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
    protolib
)

