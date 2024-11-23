
#=============================================
#
#   Infinity Systems, LLC. 2024
#
#   Simply Datetime Build Generation Script
#
#=============================================



cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(simplydatetime_lib VERSION 4.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


set(SIMPLYDT_TESTING OFF CACHE BOOL "Primary testing flag" FORCE)

if(SIMPLYDT_TESTING)
    message(STATUS "${CMAKE_PROJECT_NAME} testing - enabled")
    enable_testing()
    include(CTest)
else()
    message(STATUS "${CMAKE_PROJECT_NAME} testing - disabled")
endif()


include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)

if(SIMPLYDT_TESTING)
    add_subdirectory(3rdparty/googletest)

    include(FetchContent)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
    endif()

    add_subdirectory(tests)
endif()
