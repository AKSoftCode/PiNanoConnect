file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
    ./*.h
)

add_library(Controller.Common ${SOURCES})

#setup nlohmannjson library
include(FetchContent)

message(STATUS "FetchContent: Installing exceptxx library")

FetchContent_Declare(exceptxx
  GIT_REPOSITORY https://github.com/SergiusTheBest/exceptxx
  GIT_TAG master)

FetchContent_MakeAvailable(exceptxx)

target_include_directories(Controller.Common
PUBLIC
	${json_SOURCE_DIR}/include
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC 
	${exceptxx_SOURCE_DIR}/include
)

target_link_directories(Controller.Common
PRIVATE 
	nlohmann_json::nlohmann_json
PRIVATE
	spdlog
)
