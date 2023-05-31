file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
    ./*.h
)

add_library(Controller.DataAccess ${SOURCES})

target_include_directories(Controller.DataAccess 
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/include
PUBLIC
	${PROJECT_SOURCE_DIR}/lib
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
PUBLIC
    ${PROJECT_SOURCE_DIR}/src/Controller.Model/include
PUBLIC
	${json_SOURCE_DIR}/include
)


target_link_directories(Controller.DataAccess 
PRIVATE 
	Controller.DeviceInterface
PRIVATE
    Controller.Common
PRIVATE 
	nlohmann_json::nlohmann_json
)
