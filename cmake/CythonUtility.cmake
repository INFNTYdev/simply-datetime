
#================================
#     Cython Utility Script     #
#================================



# Mark Cython code document for compilation to CXX
function(Cythonize)

    if(NOT DEFINED Cython_FOUND OR NOT Cython_FOUND OR NOT DEFINED Cython_EXECUTABLE)
        message(FATAL_ERROR "\nCython executable is not accessible.\n")
    endif()

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS "SOURCE" "INCLUDE" "STAGE")
    set(MULTI_VALUE_ARGS "DEPENDS")

    cmake_parse_arguments(ARG "${OPTION_ARGS}" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(NOT DEFINED ARG_SOURCE)
        message(FATAL_ERROR "\n'SOURCE' argument is required.\n")
    endif()

    if(NOT DEFINED ARG_INCLUDE)
        message(FATAL_ERROR "\n'INCLUDE' argument is required.\n")
    endif()

    if(NOT EXISTS ${ARG_INCLUDE})
        message(FATAL_ERROR "\nInvalid include directory path: ${ARG_INCLUDE}\n")
    endif()

    if(NOT DEFINED ARG_DEPENDS)
        set(ARG_DEPENDS)
    endif()

    list(APPEND ARG_DEPENDS "${ARG_SOURCE}")

    foreach(file_dep IN LISTS ARG_DEPENDS)
        if(NOT EXISTS ${file_dep})
            message(FATAL_ERROR "\nInvalid Cython source file dependency: ${file_dep}\n")
        endif()
    endforeach()
    
    get_filename_component(CYTHON_SRC_FILE ${ARG_SOURCE} NAME)
    get_filename_component(CYTHON_SRC_NAME ${ARG_SOURCE} NAME_WE)

    set(CPP_OUTPUT)

    if(DEFINED ARG_STAGE)
        set(CPP_OUTPUT "${ARG_STAGE}/${CYTHON_SRC_NAME}_py.cpp")
    else()
        set(CPP_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${CYTHON_SRC_NAME}_py.cpp")
    endif()

    add_custom_command(
        OUTPUT
        "${CPP_OUTPUT}"

        COMMAND
        ${Cython_EXECUTABLE}    # Cython compiler path

        ARGS
        --cplus                 # Generate C++ files instead of C
        -3                      # Python version syntax
        -I "${ARG_INCLUDE}"     # Cython file include directory
        -o "${CPP_OUTPUT}"      # Resulting C++ wrapper path
        "${ARG_SOURCE}"         # Cython file to compile

        DEPENDS
        ${ARG_DEPENDS}

        COMMENT
        "Generating C++ code for '${CYTHON_SRC_FILE}' Cython document"
    )

    message(STATUS "Set '${CYTHON_SRC_FILE}' to be compiled in: ${CPP_OUTPUT}")

endfunction()



# Copy pure Python modules in a directory to build tree
function(Python_Source_Dir_To_Build)

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS "DIRECTORY" "STAGE")
    set(MULTI_VALUE_ARGS)

    cmake_parse_arguments(ARG "${OPTION_ARGS}" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    set(ORIGIN_PY_MODULE_DIR)
    set(DEST_PY_MODULE_DIR)

    if(NOT DEFINED ARG_DIRECTORY)
        set(ORIGIN_PY_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    else()
        set(ORIGIN_PY_MODULE_DIR ${ARG_DIRECTORY})
    endif()

    if(NOT EXISTS ${ORIGIN_PY_MODULE_DIR})
        message(FATAL_ERROR "\nInvalid Python module source directory path: ${ORIGIN_PY_MODULE_DIR}\n")
    endif()

    if(NOT DEFINED ARG_STAGE)
        message(FATAL_ERROR "\n'STAGE' argument is required.\n")
    endif()

    set(DEST_PY_MODULE_DIR ${ARG_STAGE})

    file(GLOB ORIGIN_PY_MODULES "${ORIGIN_PY_MODULE_DIR}/*.py")

    if(NOT EXISTS ${DEST_PY_MODULE_DIR})
        file(MAKE_DIRECTORY ${DEST_PY_MODULE_DIR})
    endif()

    foreach(py_module ${ORIGIN_PY_MODULES})
        file(COPY ${py_module} DESTINATION ${DEST_PY_MODULE_DIR})
    endforeach()

endfunction()



# Create Python extension module library
function(Add_Python_Library)

    if(NOT DEFINED Python_FOUND OR NOT Python_FOUND OR NOT DEFINED Python_LIBRARIES)
        message(FATAL_ERROR "\nPython libraries are not accessible.\n")
    endif()

    if(NOT DEFINED Python_INCLUDE_DIRS)
        message(FATAL_ERROR "\nPython headers are not accessible.\n")
    endif()

    if(ARGC EQUAL 0)
        message(FATAL_ERROR "\nNo name provided to Python extension module target.\n")
    endif()

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS)
    set(MULTI_VALUE_ARGS "SOURCES")

    cmake_parse_arguments(ARG "${OPTION_ARGS}" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(NOT DEFINED ARG_SOURCES)
        message(FATAL_ERROR "\n'SOURCES' argument is required.\n")
    endif()

    Python_add_library(
        ${ARGV0}

        MODULE
        ${ARG_SOURCES}
    )

    target_include_directories(
        ${ARGV0}

        PRIVATE
        ${Python_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${ARGV0}

        PRIVATE
        ${Python_LIBRARIES}
    )

    message(STATUS "Set to build '${ARGV0}' Python extension module")

endfunction()
