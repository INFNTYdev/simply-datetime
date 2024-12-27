
#============================================
#     /python/simplydt Directory Script
#============================================



set_property(GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_SRCS "")
set_property(GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_TARGETS "")



# Add Cython compiled files to a Python extension modules sources
function(Add_Module_Sources)

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS "MODULE")
    set(MULTI_VALUE_ARGS "SOURCES")

    cmake_parse_arguments(ARG "${OPTION_ARGS}" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(NOT DEFINED ARG_MODULE)
        message(FATAL_ERROR "\n'MODULE' argument is required.\n")
    endif()

    if(NOT DEFINED ARG_SOURCES)
        message(FATAL_ERROR "\n'SOURCES' argument is required.\n")
    endif()

    get_property(EXT_MOD_SRCS GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_SRCS)

    foreach(ext_mod_src ${ARG_SOURCES})
        list(APPEND EXT_MOD_SRCS "${ext_mod_src}")
    endforeach()

    set_property(GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_SRCS "${EXT_MOD_SRCS}")

endfunction()



function(Add_Module_Dependency)

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS "NEW_TARGET" "MODULE")
    set(MULTI_VALUE_ARGS "TARGETS" "SOURCES")

    cmake_parse_arguments(ARG "${OPTION_ARGS}" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(NOT DEFINED ARG_MODULE)
        message(FATAL_ERROR "\n'MODULE' argument is required.\n")
    endif()

    if(NOT DEFINED ARG_NEW_TARGET AND NOT ARG_TARGETS)
        message(FATAL_ERROR "\n'NEW_TARGET' or 'TARGETS' argument is required.\n")
    endif()

    if(NOT DEFINED ARG_SOURCES AND NOT ARG_TARGETS)
        message(FATAL_ERROR "\n'SOURCES' or 'TARGETS' argument is required.\n")
    endif()

    get_property(EXT_MOD_TRGTS GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_TARGETS)

    if(ARG_NEW_TARGET)
        add_custom_target(
            ${ARG_NEW_TARGET} ALL

            DEPENDS
            ${ARG_SOURCES}
        )

        list(APPEND EXT_MOD_TRGTS ${ARG_NEW_TARGET})

        Add_Module_Sources(
            MODULE
            ${ARG_MODULE}

            SOURCES
            ${ARG_SOURCES}
        )
    endif()

    if(ARG_TARGETS)
        foreach(module_dep ${ARG_TARGETS})
            list(APPEND EXT_MOD_TRGTS ${module_dep})
        endforeach()
    endif()

    set_property(GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_TARGETS "${EXT_MOD_TRGTS}")

endfunction()



add_subdirectory(_simplydt_lib)


#Stage_Python_Sources(STAGE "${PYTHON_PACKAGE_DIR}")
# Move other non-Python files


get_property(PYSIMPLYDT_EXT_MOD_SRCS GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_SRCS)
get_property(PYSIMPLYDT_EXT_MOD_TRGTS GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_TARGETS)
message(STATUS "\nSources:\n${PYSIMPLYDT_EXT_MOD_SRCS}\n\nTargets:\n${PYSIMPLYDT_EXT_MOD_TRGTS}\n")

#Add_Python_Library(
#    pysimplydt
#
#    SOURCES
#    "${PYSIMPLYDT_EXT_MOD_SRCS}"
#)
#
#add_dependencies(
#    pysimplydt
#
#    ${<Cython_Target_Here>}
#)
#
#target_include_directories(
#    pysimplydt
#
#    PRIVATE
#    "${CMAKE_SOURCE_DIR}/include"
#)
#
#target_link_libraries(
#    pysimplydt
#
#    PRIVATE
#    simplydt
#)
#
#add_custom_command(
#    TARGET
#    pysimplydt
#
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#        "$<TARGET_FILE:pysimplydt>"
#        "${PYTHON_PACKAGE_DIR}/_simplydt_lib/$<TARGET_FILE_NAME:pysimplydt>"
#)
