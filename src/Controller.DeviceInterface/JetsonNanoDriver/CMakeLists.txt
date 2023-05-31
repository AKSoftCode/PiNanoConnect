file(GLOB_RECURSE SOURCES
	./*.cpp
	./*.hpp
        #${PROJECT_SOURCE_DIR}/lib/ABElectronics/ADCDACPi/ABE_ADCDACPi.h
        #${PROJECT_SOURCE_DIR}/lib/ABElectronics/ADCDACPi/ABE_ADCDACPi.cpp
)

add_library(JetsonNanoDriver SHARED  ${SOURCES})

add_compile_definitions(HAL_COMPILING)

option(JETSON_NANO_HOST "Use Jetson GPIO" ON)

include(FetchContent)
if(JETSON_NANO_HOST)
        message("Installing JetsonGPIO for Jetson Device")
	add_compile_definitions(JETSON_NANO_HOST=1)
	#Setup Jetson GPIO
	FetchContent_Declare(
	  JetsonGPIO 
	  GIT_REPOSITORY https://github.com/pjueon/JetsonGPIO.git 
	  GIT_TAG master
	)
	FetchContent_MakeAvailable(JetsonGPIO)

        target_link_libraries(JetsonNanoDriver
            PRIVATE
                JetsonGPIO::JetsonGPIO
            PRIVATE
                setila
            PRIVATE
                Controller.Common)
else()
        message("Installing wiringpi for Raspberry pi Device")
	add_compile_definitions(JETSON_NANO_HOST=0)
	include(FetchContent)
	FetchContent_Declare(
		wiringpi
		GIT_REPOSITORY https://github.com/WiringPi/WiringPi.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(wiringpi)

        message(STATUS "Build wiringpi")
 #       execute_process(COMMAND ./build
 #                       WORKING_DIRECTORY ${wiringpi_SOURCE_DIR}
 #                       RESULT_VARIABLE WIRING_PI_BUILD_RESULT)
 #       if(NOT WIRING_PI_BUILD_RESULT EQUAL "0")
 #           message(FATAL_ERROR "WiringPi Installation Failed with ${GIT_SUBMODULE_RESULT}.")
 #       endif()

 #       add_custom_target(
 #                  wiringPi ALL
 #                  COMMAND ./build
 #                  WORKING_DIRECTORY  ${wiringpi_SOURCE_DIR}
 #                  COMMENT "WiringPi Installation"
 #          )


        target_link_libraries(JetsonNanoDriver
         PRIVATE
            wiringPi
         PRIVATE
             setila
          PRIVATE
             Controller.Common)
endif()



target_include_directories(JetsonNanoDriver 
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/../include
PUBLIC
	${PROJECT_SOURCE_DIR}/src/Controller.Common/include
PUBLIC 
	${PROJECT_SOURCE_DIR}/lib/spdlog/include
PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/libsetila/include
#PUBLIC
#        ${PROJECT_SOURCE_DIR}/lib/ABElectronics/ADCDACPi
)
