
#=========================================
#     Cython Compiler Locator Script     #
#=========================================



if(DEFINED Cython_FOUND AND Cython_FOUND)
    message(WARNING "\nCython has already been located.\n")
    return()
endif()


set(TARGET_PACKAGE "Cython")
set(TARGET_PACKAGE_NAMES)
list(APPEND TARGET_PACKAGE_NAMES "cython" "cython.py" "cython3")

find_program(
    ${TARGET_PACKAGE}_EXECUTABLE

    NAMES
    ${TARGET_PACKAGE_NAMES}

    DOC
    "Path to ${TARGET_PACKAGE} package target"
)


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    ${TARGET_PACKAGE}

    REQUIRED_VARS
    ${TARGET_PACKAGE}_EXECUTABLE
)

if(NOT DEFINED ${TARGET_PACKAGE}_FOUND OR NOT ${TARGET_PACKAGE}_FOUND)
    message(WARNING "\nFailed to locate ${TARGET_PACKAGE} on the system.\n")
endif()
