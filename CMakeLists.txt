
cmake_minimum_required(VERSION 3.16)

project("simply-datetime" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compile/${PST_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compile/${PST_NAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compile/${PST_NAME}")

enable_testing()
include(CTest)



# Include
include_directories("${PROJECT_SOURCE_DIR}/include")



# Build
add_subdirectory(external)
add_subdirectory(src)



# Developer
add_subdirectory(tests)
