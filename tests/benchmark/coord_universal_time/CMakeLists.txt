
#=================================================================
#     /tests/benchmark/coord_universal_time Directory Script
#=================================================================



add_executable(
	utc_utility_benchmark

	"${CMAKE_CURRENT_SOURCE_DIR}/utc_util_bm.cpp"
)

target_link_libraries(
	utc_utility_benchmark

	PRIVATE
	benchmark_external
	simplydt
)
