file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
    ./*.h
	./*.cc
)


find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)


set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake)

#
# Protobuf/Grpc source files
#
set(PROTO_FILES
    Proto/Controller.proto
)

#
# Add Library target with protobuf sources
#
add_library(Controller ${PROTO_FILES} ${SOURCES})

target_include_directories(Controller 
PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/Controller.Model/include
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
)

#
# Compile protobuf and grpc files in myproto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET Controller LANGUAGE cpp)
protobuf_generate(TARGET Controller LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")


target_link_libraries(Controller
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
    PUBLIC
        Controller.Model
    PUBLIC 
        Controller.DataAccess
    PRIVATE
        Controller.Common
)

