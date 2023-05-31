
if(NOT WIN32)
    add_subdirectory(JetsonNanoDriver)
endif()

add_subdirectory(JetsonNanoSimulationDriver)

set(SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/IDeviceInterface.h
	${CMAKE_CURRENT_LIST_DIR}/include/IHAL.h
	${CMAKE_CURRENT_LIST_DIR}/DeviceInterface.hpp
	${CMAKE_CURRENT_LIST_DIR}/DeviceInterface.cpp
)

add_library(Controller.DeviceInterface  ${SOURCES})

#setup dylib library
message(STATUS "FetchContent: Installing dylib library")
include(FetchContent)
FetchContent_Declare(
    dylib
    GIT_REPOSITORY "https://github.com/martin-olivier/dylib"
    GIT_TAG        "v2.1.0"
)

FetchContent_MakeAvailable(dylib)

target_include_directories(Controller.DeviceInterface 
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/../include
PUBLIC
	${PROJECT_SOURCE_DIR}/lib
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
PUBLIC
    ${dylib_SOURCE_DIR}/include
PUBLIC
    ${json_SOURCE_DIR}/include
)

target_link_libraries(Controller.DeviceInterface
PRIVATE
	Controller.Common
)