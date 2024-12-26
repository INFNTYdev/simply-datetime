
#================================
#     Cython Utility Script     #
#================================



# Mark Cython code document for compilation to CXX
function(Cython_Mark_For_Compilation)

    if(NOT DEFINED Cython_FOUND OR NOT Cython_FOUND OR NOT DEFINED Cython_EXECUTABLE)
        message(FATAL_ERROR "\nCython executable is not present.\n")
    endif()

    set(OPTION_ARGS)
    set(SINGLE_VALUE_ARGS "SOURCE" "INCLUDE" "INSTALL")
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

    if(DEFINED ARG_INSTALL)
        set(CPP_OUTPUT "${ARG_INSTALL}/${CYTHON_SRC_NAME}_py.cpp")
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



# Create Python extension module library
function(Add_Python_Library _name _cpp_py_src)

    if(NOT DEFINED Python_FOUND OR NOT Python_FOUND OR NOT DEFINED Python_LIBRARIES)
        message(FATAL_ERROR "\nCannot create Python extensions without Python libraries.\n")
    endif()

    if(NOT DEFINED Python_INCLUDE_DIRS)
        message(FATAL_ERROR "\nMissing Python headers.\n")
    endif()

    Python_add_library(
        ${_name}

        MODULE
        "${_cpp_py_src}"
    )

    target_include_directories(
        ${_name}

        PRIVATE
        ${Python_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${_name}

        PRIVATE
        ${Python_LIBRARIES}
    )

endfunction()
