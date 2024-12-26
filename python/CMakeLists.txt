
#===================================
#     /python Directory Script
#===================================



find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(Cython REQUIRED)

include(CythonUtility)


Cython_Mark_For_Compilation(
    SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt/simplydt_lib/_core.pyx"

    INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt/simplydt_lib"

    DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/simplydt/simplydt_lib/_core.pxd"

    INSTALL
    "${CMAKE_CURRENT_BINARY_DIR}/simplydt/simplydt_lib"
)
