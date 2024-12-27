
#===================================
#     /python Directory Script
#===================================



find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(Cython REQUIRED)

include(CythonUtility)


set(
    ${LOCAL_PROJECT_SCOPE}_PYTHON_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE STRING
    "Python Simply Datetime directory"
)

set(
    ${LOCAL_PROJECT_SCOPE}_CYTHON_ARTIFACT_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/cython"
    CACHE STRING
    "Cython intermediate compilation directory"
)

set(
    ${LOCAL_PROJECT_SCOPE}_PYTHON_SRC_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt"
    CACHE STRING
    "Python Simply Datetime source tree root"
)

set(
    ${LOCAL_PROJECT_SCOPE}_PYTHON_PACKAGE_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/simplydt"
    CACHE STRING
    "Simply Datetime Python package build directory root"
)

set(CYTHON_ARTIFACT_DIR ${${LOCAL_PROJECT_SCOPE}_CYTHON_ARTIFACT_DIR})
set(PYTHON_SRC_DIR ${${LOCAL_PROJECT_SCOPE}_PYTHON_SRC_DIR})
set(PYTHON_PACKAGE_DIR ${${LOCAL_PROJECT_SCOPE}_PYTHON_PACKAGE_DIR})


add_subdirectory("simplydt")
