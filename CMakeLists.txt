cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(
  Vultra
  VERSION 25.0.0
  DESCRIPTION "A simple Vulkan rendering engine"
  LANGUAGES C
  HOMEPAGE_URL "https://github.com/SOHNE/Vultra"
)

message(STATUS "=========================================================================")
message(STATUS " Copyright (c), 2025                     SOHNE, Leandro Peres (@zschzen) ")
message(STATUS "=========================================================================")
message(STATUS "                                                                         ")
message(STATUS "     oooooo     oooo             oooo      .                             ")
message(STATUS "      `888.     .8'              `888    .o8                             ")
message(STATUS "       `888.   .8'   oooo  oooo   888  .o888oo oooo d8b  .oooo.          ")
message(STATUS "        `888. .8'    `888  `888   888    888   `888''8P `P  )88b         ")
message(STATUS "         `888.8'      888   888   888    888    888      .oP'888         ")
message(STATUS "          `888'       888   888   888    888 .  888     d8(  888         ")
message(STATUS "           `8'        `V88V'V8P' o888o   '888' d888b    `Y888''8o        ")
message(STATUS "     v${PROJECT_VERSION}                                                 ")
message(STATUS "                                                                         ")
message(STATUS "=========================================================================")
message(STATUS " https://sohne.github.io/vultra                     zlib/libpng licensed ")

# Determine if is the main project
set(IS_MAIN ${PROJECT_IS_TOP_LEVEL})

# --------------------------------------------------------------------
# Paths
# --------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/vultra)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# --------------------------------------------------------------------
# Options
# --------------------------------------------------------------------
include(CMakeOptions.cmake)

# --------------------------------------------------------------------
# Output Directories
# --------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# --------------------------------------------------------------------
# Global Properties
# --------------------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# --------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------
message(STATUS "= CPM.cmake ============================================================= ")

set(EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/external")
set(INCLUDE_DEPS_DIR "")
set(LINK_DEPS "")

list(APPEND INCLUDE_DEPS_DIR "${EXTERNAL_DIR}")

include(cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

include(cmake/tools.cmake)

# Add GLFW
include(deps/glfw)
include(deps/shaderc)
include(deps/cglm)

CPMAddPackage("gh:cpm-cmake/CPMLicenses.cmake@0.0.7")
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.13.0")
CPMAddPackage("gh:TheLartians/GroupSourcesByFolder.cmake@1.0")

# --------------------------------------------------------------------
# Subdirectories
# --------------------------------------------------------------------
add_subdirectory(src vultra)

# --------------------------------------------------------------------
# Installation Configuration
# --------------------------------------------------------------------
string(TOLOWER ${PROJECT_NAME}/vversion.h VERSION_HEADER_LOCATION)
string(TOLOWER ${PROJECT_NAME}/vexport.h EXPORT_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  EXPORT_HEADER "${EXPORT_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
  DEPENDENCIES "Ccache 1.2.5;GLFW 3.4"
)

# --------------------------------------------------------------------
# License collector
# --------------------------------------------------------------------
# Usage: --build build --target write-licenses
cpm_licenses_create_disclaimer_target(
  write-licenses "${CMAKE_CURRENT_BINARY_DIR}/third_party.txt" "${CPM_PACKAGES}"
)

message(STATUS "= VULTRA ================================================================ ")

