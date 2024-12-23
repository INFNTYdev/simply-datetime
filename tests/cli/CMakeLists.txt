
#======================================
#     /tests/cli Directory Script
#======================================



add_executable(dev_executable "${CMAKE_CURRENT_SOURCE_DIR}/dev_exe.cpp")

target_link_libraries(
    dev_executable

    PRIVATE
    simplydt
)
