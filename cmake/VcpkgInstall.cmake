#=======================================VCPKG=====================================================
#Build/Install vcpkg as needed

if (WIN32)
        set(BOOSTRAP_VCPKG_CMD "${CMAKE_CURRENT_SOURCE_DIR}/lib/vcpkg/bootstrap-vcpkg.bat")   
        set(VCPKG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/vcpkg/vcpkg.exe")  
elseif(UNIX AND NOT APPLE)
        set(BOOSTRAP_VCPKG_CMD "${CMAKE_CURRENT_SOURCE_DIR}/lib/vcpkg/bootstrap-vcpkg.sh")     
        set(VCPKG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/vcpkg/vcpkg") 
endif()


function(vcpkg_configure)
    message(STATUS "Vcpkg Configure")
    execute_process(COMMAND ${BOOSTRAP_VCPKG_CMD} -disableMetrics
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                    RESULT_VARIABLE CMD_ERROR
                    COMMAND_ECHO STDOUT 
                    OUTPUT_FILE CMD_OUTPUT
                    ECHO_OUTPUT_VARIABLE )
    MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
    MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})

    execute_process(COMMAND ${VCPKG_PATH} integrate install
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                    RESULT_VARIABLE CMD_ERROR
                    COMMAND_ECHO STDOUT 
                    OUTPUT_FILE CMD_OUTPUT
                    ECHO_OUTPUT_VARIABLE )
    MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
    MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
endfunction()


function(vcpkg_deps_install VCPKG_DEPS_LIST)
    message("Installing Pakages: " ${VCPKG_DEPS_LIST})
    foreach(DEPS ${VCPKG_DEPS_LIST})
        message(STATUS "Dependency Installtion for package: " ${DEPS})
        execute_process(COMMAND ${VCPKG_PATH} install ${DEPS} --editable
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                        RESULT_VARIABLE CMD_ERROR
                        COMMAND_ECHO STDOUT 
                        OUTPUT_FILE CMD_OUTPUT
                        ECHO_OUTPUT_VARIABLE )
        MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
        MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
    endforeach()
endfunction()
#==============================================================================================