
#==========================================================
#     /tests/unit/gregorian_calendar Directory Script
#==========================================================



add_executable(
	gregorian_utility_tests

	"${CMAKE_CURRENT_SOURCE_DIR}/greg_util_tests.cpp"
)

target_link_libraries(
	gregorian_utility_tests

	PRIVATE
	googletest_external
	simplydt
)
