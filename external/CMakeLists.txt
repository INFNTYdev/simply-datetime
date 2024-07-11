
# \external\ DIRECTORY CMAKE SCRIPT


project(ExternalDependencies LANGUAGES CXX)

add_subdirectory(googletest)
include_directories("${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include")
