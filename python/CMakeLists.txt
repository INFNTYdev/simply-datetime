
#===================================
#     /python Directory Script
#===================================



find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(Cython REQUIRED)

include(CythonUtility)


Cythonize(
    SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt/_simplydt_lib/gregorian_util.pyx"

    INCLUDE
    "${CMAKE_SOURCE_DIR}/include"

    DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt/_simplydt_lib/core.pxd"

    INSTALL
    "${CMAKE_CURRENT_BINARY_DIR}/simplydt/_simplydt_lib"
)


Add_Python_Library(
    pysimplydt

    SOURCES
    "${CMAKE_CURRENT_BINARY_DIR}/simplydt/_simplydt_lib/gregorian_util_py.cpp"
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
