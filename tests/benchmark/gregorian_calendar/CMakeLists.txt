
#===============================================================
#     /tests/benchmark/gregorian_calendar Directory Script
#===============================================================



add_executable(
	gregorian_util_benchmark

	"${CMAKE_CURRENT_SOURCE_DIR}/greg_util_bm.cpp"
)

target_link_libraries(
	gregorian_util_benchmark

	PRIVATE
	benchmark_external
	simplydt
)
