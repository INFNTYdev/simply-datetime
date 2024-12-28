
#============================================
#     /python/simplydt Directory Script
#============================================



set_property(GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_SOURCES "")
set_property(GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_TARGETS "")


include(PythonUtility)


Cythonize(
    SOURCE
    "${PYTHON_SRC_DIR}/_simplydt_lib/gregorian_util.pyx"

    INCLUDE
    "${CMAKE_SOURCE_DIR}/include"

    DEPENDS
    "${PYTHON_SRC_DIR}/_simplydt_lib/core.pxd"

    STAGE
    "${CYTHON_ARTIFACT_DIR}/_simplydt_lib"
)

Add_Module_Dependencies(
    NO_TEMP
    
    MODULE
    pysimplydt

    NEW_TARGET
    py_gregorian_util

    SOURCES
    ${LAST_CYTHONIZED}
)

Stage_Python_Files(
    DIRECTORY
    "${PYTHON_SRC_DIR}/_simplydt_lib"

    STAGE
    "${PYTHON_PACKAGE_DIR}/_simplydt_lib"
)


get_property(PYSIMPLYDT_EXT_MOD_SRCS GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_SOURCES)
get_property(PYSIMPLYDT_EXT_MOD_TRGTS GLOBAL PROPERTY pysimplydt_EXTENSION_MODULE_TARGETS)

Add_Python_Library(
    pysimplydt

    SOURCES
    ${PYSIMPLYDT_EXT_MOD_SRCS}
)

target_include_directories(
    pysimplydt

    PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(
    pysimplydt

    PRIVATE
    simplydt
)

add_custom_command(
    TARGET
    pysimplydt

    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:pysimplydt>"
        "${PYTHON_PACKAGE_DIR}/_simplydt_lib/$<TARGET_FILE_NAME:pysimplydt>"
)

Stage_Python_Files(STAGE "${PYTHON_PACKAGE_DIR}")
# Move other non-Python files
