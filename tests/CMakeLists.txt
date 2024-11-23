
#==============================#
#   \tests\ Directory Script   #
#==============================#



add_library(googletest_external INTERFACE)

target_include_directories(
    googletest_external

    INTERFACE
    "${googletest_SOURCE_DIR}/googletest/include"
)

target_link_libraries(
    googletest_external

    INTERFACE
    gtest
    gtest_main
)


add_executable(simplydt_dev "dev_exe.cpp")
target_link_libraries(simplydt_dev PUBLIC simplydtlib)


# Unit Tests (Deprecated)
# add_executable(DatetimeClassTests "unit/datetime_cls/datetime_tests.cpp")
# 
# target_link_libraries(
#     DatetimeClassTests
#     
#     PRIVATE
#     googletest_external
#     simplydtlib
# )
# 
# gtest_discover_tests(DatetimeClassTests)
