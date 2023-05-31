file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
    ./*.h)

add_executable(Controller.Server main.cpp)

target_include_directories(Controller.Server 
PUBLIC 
	${PROJECT_SOURCE_DIR}/src/Controller/include
PUBLIC 
	${PROJECT_SOURCE_DIR}/src/Controller.DeviceInterface/include
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
)


target_link_directories(Controller.Server PUBLIC ${json_BINARY_DIR})


target_link_libraries(Controller.Server 
PUBLIC
	Controller
PUBLIC
	Controller.Model
PUBLIC
	Controller.DeviceInterface
PRIVATE
	Controller.Common
)


#Copy Dependencies
configure_file(${PROJECT_SOURCE_DIR}/src/Controller.Common/Controller.ini ${CMAKE_CURRENT_BINARY_DIR}/Controller.ini COPYONLY)
file(COPY ${PROJECT_SOURCE_DIR}/src/Controller.Common/Config DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)


