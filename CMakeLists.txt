cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake)
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/lib/vcpkg-export/scripts/buildsystems/vcpkg.cmake)


project(Controller.Server VERSION 1.0)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "Binary folder and source folder should be separate!!")
endif()

#global Compiler options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${PROJECT_SOURCE_DIR}/cmake/Submodule.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/VcpkgInstall.cmake)

option(GIT_SUBMODULE "Check Submodule during build" ON)
option(VCPKG_CONFIGURE "Install VCPKG during build" ON)
option(VCPKG_INSTALL_DEPS "Install VCPKG dependecies build" ON)

#update git submodule
if(GIT_SUBMODULE)
	submodule_update()
endif()

#vcpkg configure
if(VCPKG_CONFIGURE)
    vcpkg_configure()
endif()

#vcpkg install dependency pkgs
if(VCPKG_INSTALL_DEPS)  
        #set(VCPKG_DEPS_LIST "")
        if (WIN32)
            set(VCPKG_DEPS_LIST
                    protobuf:x64-windows
                    grpc:x64-windows
                    )
        elseif(UNIX AND NOT APPLE)
            #sudo VCPKG_FORCE_SYSTEM_BINARIES=1 ./vcpkg install protobuf --editable

            #sudo VCPKG_FORCE_SYSTEM_BINARIES=1 ./vcpkg install grpc --editable
            set(VCPKG_DEPS_LIST
                    protobuf
                    grpc
                    )
        endif()


    vcpkg_deps_install("${VCPKG_DEPS_LIST}")
endif()

#setup nlohmannjson library
include(FetchContent)

message(STATUS "FetchContent: Installing nlohmannjson library")

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory( ${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#Threads
find_package(Threads REQUIRED)


add_subdirectory(lib)
add_subdirectory(src)
