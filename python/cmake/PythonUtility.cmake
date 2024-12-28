
#================================
#     Python Utility Script     #
#================================



# Add compiled Cython files to a Python extension modules sources
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

    get_property(PY_EXT_MOD_SRCS GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_SRCS)

    if(NOT DEFINED PY_EXT_MOD_SRCS)
        message(FATAL_ERROR "\nNo global extension module source property exists for '${ARG_MODULE}' target.\n")
    endif()

    foreach(ext_mod_src ${ARG_SOURCES})
        list(APPEND PY_EXT_MOD_SRCS "${ext_mod_src}")

        get_filename_component(DIRECTORY_PATH ${ext_mod_src} DIRECTORY)

        if(NOT EXISTS ${DIRECTORY_PATH})
            file(MAKE_DIRECTORY ${DIRECTORY_PATH})
        endif()

        file(WRITE ${ext_mod_src} "\n// Temporary dummy file for ${ARG_MODULE} Python extension module target\n")
    endforeach()

    set_property(GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_SRCS "${PY_EXT_MOD_SRCS}")

endfunction()



# Add targets to Python extension module dependencies
function(Add_Module_Dependencies)

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

    get_property(PY_EXT_MOD_TRGTS GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_TARGETS)

    if(NOT DEFINED PY_EXT_MOD_TRGTS)
        message(FATAL_ERROR "\nNo global extension module targets property exists for '${ARG_MODULE}' target.\n")
    endif()

    if(ARG_NEW_TARGET)
        add_custom_target(
            ${ARG_NEW_TARGET} ALL

            DEPENDS
            ${ARG_SOURCES}
        )

        list(APPEND PY_EXT_MOD_TRGTS ${ARG_NEW_TARGET})

        Add_Module_Sources(
            MODULE
            ${ARG_MODULE}

            SOURCES
            ${ARG_SOURCES}
        )
    endif()

    if(ARG_TARGETS)
        foreach(module_dep ${ARG_TARGETS})
            list(APPEND PY_EXT_MOD_TRGTS ${module_dep})
        endforeach()
    endif()

    set_property(GLOBAL PROPERTY ${ARG_MODULE}_EXTENSION_MODULE_TARGETS "${PY_EXT_MOD_TRGTS}")

endfunction()
