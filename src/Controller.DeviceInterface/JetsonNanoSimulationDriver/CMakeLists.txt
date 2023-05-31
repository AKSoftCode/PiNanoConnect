file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
	./*.tpp
)

add_library(JetsonNanoSimDriver SHARED ${SOURCES})

add_compile_definitions(HAL_COMPILING)

target_include_directories(JetsonNanoSimDriver 
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/../include
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
)

target_link_libraries(JetsonNanoSimDriver 
PRIVATE
   Controller.Common
)
