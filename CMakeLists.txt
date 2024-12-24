
#==================================================
#
#     Infinity Systems, LLC. 2025 and
#     Jamon Bailey
#
#     Simply Datetime Build Generation Script
#
#==================================================



cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(LOCAL_CMAKE_PROJECT_NAME "simply_datetime_core")

project("${LOCAL_CMAKE_PROJECT_NAME}" VERSION 4.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(LOCAL_PROJECT_SCOPE "SIMPLYDT")


set(CLI_DEBUGGING OFF)
set(UNIT_TESTING OFF)

set(BUILD_PYTHON_EXT_MODULES OFF)

if(DEFINED CACHE{${LOCAL_PROJECT_SCOPE}_PROJECT_TESTING} AND ${LOCAL_PROJECT_SCOPE}_PROJECT_TESTING)
	message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} testing - enabled")
	set(UNIT_TESTING ON)
	enable_testing()
else()
	message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} testing - disabled")
endif()

if(DEFINED CACHE{${LOCAL_PROJECT_SCOPE}_PROJECT_CLI_DEBUG} AND ${LOCAL_PROJECT_SCOPE}_PROJECT_CLI_DEBUG)
	message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} CLI debugging - enabled")
	set(CLI_DEBUGGING ON)

	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		message(WARNING "Building CLI debugging executables on release?")
	endif()
else()
	message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} CLI debugging - disabled")
endif()


if(DEFINED CACHE{${LOCAL_PROJECT_SCOPE}_PY_EXT_MODULES} AND ${LOCAL_PROJECT_SCOPE}_PY_EXT_MODULES)
	message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} Python extension module build - enabled")
	set(BUILD_PYTHON_EXT_MODULES ON)
endif()


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)
# Other subdirs...


if(BUILD_PYTHON_EXT_MODULES)
	add_subdirectory(python)
endif()


if(UNIT_TESTING)
	add_subdirectory(3rdparty/googletest)
	add_subdirectory(3rdparty/benchmark)
endif()

if(CLI_DEBUGGING OR UNIT_TESTING)
	add_subdirectory(tests)
endif()

