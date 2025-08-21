# --------------------------------------------------------------------
# Project Setup
# --------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26...4.0)
project(Vultra_Example LANGUAGES C)

# --------------------------------------------------------------------
# Output Directories
# --------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# --------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------
include(../cmake/CPM.cmake)
include(../cmake/tools.cmake)

CPMAddPackage(NAME Vultra SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage("gh:TheLartians/GroupSourcesByFolder.cmake@1.0")

# --------------------------------------------------------------------
# Find all examples files recursively
# --------------------------------------------------------------------
file(GLOB_RECURSE EXAMPLE_SOURCE_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

foreach(SOURCE_FILE ${EXAMPLE_SOURCE_FILES})
    # Get the filename without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})

    # Link Vultra
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC Vultra::Vultra)

    # Platform-Specific Configuration
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
        set_property(TARGET ${EXECUTABLE_NAME} PROPERTY WIN32_EXECUTABLE true)
        target_link_options(${EXECUTABLE_NAME} PUBLIC -static -static-libgcc -static-libstdc++)
    endif()

    # Group sources
    GroupSourcesByFolder(${EXECUTABLE_NAME})
endforeach()
