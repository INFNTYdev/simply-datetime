
#================================
#     Cython Utility Script     #
#================================



# Mark Cython code document for compilation to CXX
function(Cython_Mark_For_Compilation _cython_src _cpp_output)

    if(NOT DEFINED Cython_FOUND OR NOT Cython_FOUND OR NOT DEFINED Cython_EXECUTABLE)
        message(FATAL_ERROR "\nCannot compile Cython files without Cython executable.\n")
    endif()

    if(NOT EXISTS ${_cython_src})
        message(FATAL_ERROR "\nInvalid Cython source: ${_cython_src}\n")
    endif()
    
    get_filename_component(cython_src_file ${_cython_src} NAME)

    # Compile with NO include directory
    if(ARGC EQUAL 2)

        add_custom_command(
            OUTPUT
            "${_cpp_output}"

            COMMAND
            ${Cython_EXECUTABLE}

            ARGS
            --cplus
            -3
            -o "${_cpp_output}"
            "${_cython_src}"

            DEPENDS
            "${cython_src_file}"

            COMMENT
            "Generating C++ code for '${cython_src_file}' Cython document"
        )

    # Compile with include directory
    elseif(ARGC EQUAL 3)

        set(src_header_dir ${ARGV2})

        add_custom_command(
            OUTPUT
            "${_cpp_output}"

            COMMAND
            ${Cython_EXECUTABLE}

            ARGS
            --cplus
            -3
            -I "${src_header_dir}"
            -o "${_cpp_output}"
            "${_cython_src}"

            DEPENDS
            "${cython_src_file}"

            COMMENT
            "Generating C++ code for '${cython_src_file}' Cython document"
        )

    else()
        message(FATAL_ERROR "\nInvalid number of arguments provided to function.\n")
    endif()

    message(STATUS "Set '${cython_src_file}' to be compiled to: ${_cpp_output}")

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
