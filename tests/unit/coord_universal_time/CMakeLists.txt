
#============================================================
#     /tests/unit/coord_universal_time Directory Script
#============================================================



add_executable(
	utc_utility_tests

	"${CMAKE_CURRENT_SOURCE_DIR}/utc_util_tests.cpp"
)

target_link_libraries(
	utc_utility_tests

	PRIVATE
	googletest_external
	simplydt
)
