
#===================================
#     /python Directory Script
#===================================



find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(Cython REQUIRED)

include(CythonUtility)
