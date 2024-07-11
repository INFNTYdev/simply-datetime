
# \tests\ DIRECTORY CMAKE SCRIPT


project(DatetimeTesting LANGUAGES CXX)

add_executable(dev_executable "dev_exe.cpp")
#target_link_libraries(dev_executable PUBLIC simplydtlib)


include(GoogleTest)


# Unit Tests
add_executable(DateSequenceTests "unit/dt_sequence_tests/date_tests.cpp")
target_link_libraries(DateSequenceTests PRIVATE gtest gtest_main)
gtest_discover_tests(DateSequenceTests)
