
#==============================================
#     /tests/unit/string Directory Script
#==============================================



add_executable(
	string_util_tests

	"${CMAKE_CURRENT_SOURCE_DIR}/string_util_tests.cpp"
)

target_link_libraries(
	string_util_tests

	PRIVATE
	googletest_external
	simplydt
)
