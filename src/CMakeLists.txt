
#================================
#     /src Directory Script
#================================



add_subdirectory(meta)


set(PRIMARY_BINARY_NAME "${${LOCAL_PROJECT_SCOPE}_PRIMARY_BINARY_NAME}")

# EXECUTABLE BINARY
if(${LOCAL_PROJECT_SCOPE}_INTERFACE_TYPE STREQUAL "CLI" OR ${LOCAL_PROJECT_SCOPE}_INTERFACE_TYPE STREQUAL "GUI")

    set(ENTRY_POINT_SRC "<MAIN_CPP_FILE>.cpp")

    # COMMAND LINE EXECUTABLE
    if(${LOCAL_PROJECT_SCOPE}_INTERFACE_TYPE STREQUAL "CLI")

        if(APPLE)
            message(STATUS "COMMAND LINE EXECUTABLE SOFTWARE FOR MACOS (INCOMPLETE)")
        else()
            add_executable("${PRIMARY_BINARY_NAME}" ${ENTRY_POINT_SRC})
        endif()

    # GRAPHICAL USER INTERFACE EXECUTABLE
    elseif(${LOCAL_PROJECT_SCOPE}_INTERFACE_TYPE STREQUAL "GUI")

        if(APPLE)
            set(MACOS_PLIST_SRC ${CMAKE_SOURCE_DIR}/config/platform/macos/Info.plist)

            add_executable("${PRIMARY_BINARY_NAME}" MACOSX_BUNDLE ${ENTRY_POINT_SRC})
            set_target_properties("${PRIMARY_BINARY_NAME}" PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${MACOS_PLIST_SRC})
        else()
            set(WIN32_DPI_MANIFEST_SRC ${CMAKE_SOURCE_DIR}/config/platform/windows/win32dpi.manifest)

            add_executable("${PRIMARY_BINARY_NAME}" WIN32 ${ENTRY_POINT_SRC} ${WIN32_DPI_MANIFEST_SRC})
        endif()

    endif()

# LIBRARY BINARY
else()

    if(APPLE)
        message(STATUS "LIBRARY FOR MACOS (INCOMPLETE)")
    else()
        message(STATUS "LIBRARY FOR LINUX OR WINDOWS (INCOMPLETE)")
    endif()
    
endif()

target_include_directories(
    "${PRIMARY_BINARY_NAME}"

    PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)


add_library(CompileOptions INTERFACE)

target_compile_features(
    CompileOptions

    INTERFACE
    cxx_std_20
)


# Source subdirs...


target_link_libraries(
    "${PRIMARY_BINARY_NAME}"

    PUBLIC
    CompileOptions
)
