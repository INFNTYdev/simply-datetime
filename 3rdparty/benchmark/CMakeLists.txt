
#===============================================
#     /3rdparty/benchmark Directory Script
#===============================================



message(STATUS "Fetching Google Benchmark library source...")

include(FetchContent)

FetchContent_Declare(
	benchmark

	GIT_REPOSITORY
	https://github.com/google/benchmark.git

	GIT_TAG
	v1.9.1
)

#FetchContent_GetProperties(benchmark)

#set(googletest_BUILD_DIR "${FETCHCONTENT_BASE_DIR}/googletest-build" PARENT_SCOPE)

FetchContent_MakeAvailable(benchmark)
