
#=======================================Submodule=================================================
find_package(Git QUIET)

function(submodule_update)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        #Update submodule as needed
        message(STATUS "Submodule Update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMODULE_RESULT}.")
        endif()
    endif()
endfunction()
#=================================================================================================