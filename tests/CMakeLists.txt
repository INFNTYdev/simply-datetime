
# \tests\ DIRECTORY CMAKE SCRIPT


project(DatetimeTesting LANGUAGES CXX)

add_executable(dev_executable "dev_exe.cpp")
#target_link_libraries(dev_executable PUBLIC simplydtlib)


include(GoogleTest)


# Unit Tests
add_executable(VirtualDateSequenceTests "unit/dt_sequence_tests/date_tests.cpp")
target_link_libraries(VirtualDateSequenceTests PRIVATE gtest gtest_main)
gtest_discover_tests(VirtualDateSequenceTests)
