file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
    ./*.h
)

add_library(Controller.Model ${SOURCES})

target_include_directories(Controller.Model 
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/include
PUBLIC
	${PROJECT_SOURCE_DIR}/lib
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.DataAccess/include
PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Controller.DeviceInterface/include
PUBLIC
	${json_SOURCE_DIR}/include
PUBLIC
	${exceptxx_SOURCE_DIR}/include
)


target_link_directories(Controller.Model 
PUBLIC 
	Controller.DeviceInterface
PUBLIC 
	Controller.DataAccess
PRIVATE
	Controller.Common
PRIVATE 
	nlohmann_json::nlohmann_json
)