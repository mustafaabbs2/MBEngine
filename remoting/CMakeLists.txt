cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(remoting)


find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(SOURCES_SERVER
    src/headservice.cpp
)

set(SOURCES_CLIENT
    src/headclient.cpp
)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)


set(PROTOS
    kvp.proto
)


protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})  #generates the message classes
#grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})   #generates the service classes


# Building server
add_executable(rpc_server
    ${SOURCES_SERVER}
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)
target_link_libraries(rpc_server
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)
# Building client
add_executable(rpc_client
    ${SOURCES_CLIENT}
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(rpc_client
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)