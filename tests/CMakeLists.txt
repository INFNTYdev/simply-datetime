
# \tests\ DIRECTORY CMAKE SCRIPT


project(DatetimeTesting LANGUAGES CXX)

add_executable(dev_executable "dev_exe.cpp")
target_link_libraries(dev_executable PUBLIC simplydtlib)


include(GoogleTest)


# Unit Tests
add_executable(DatetimeClassTests "unit/datetime_cls/datetime_tests.cpp")
target_link_libraries(DatetimeClassTests PRIVATE gtest gtest_main simplydtlib)
gtest_discover_tests(DatetimeClassTests)
