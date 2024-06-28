
# \tests\ DIRECTORY CMAKE SCRIPT


project(DatetimeTesting LANGUAGES CXX)

add_executable(dev_executable "dev_exe.cpp")
#target_link_libraries(dev_executable PUBLIC NULL)


include(GoogleTest)


# Unit Tests
