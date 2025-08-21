find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(SHADERC QUIET shaderc)
endif()

if(NOT SHADERC_FOUND)
    message(STATUS "System shaderc not found, fetching using CPM")

    CPMAddPackage(
        NAME shaderc
        GITHUB_REPOSITORY google/shaderc
        GIT_TAG v2025.3
        OPTIONS
            "SHADERC_SKIP_TESTS ON"
            "SHADERC_SKIP_EXAMPLES ON"
            "SHADERC_SKIP_COPYRIGHT_CHECK ON"
    )

    list(APPEND LINK_DEPS $<TARGET_OBJECTS:shaderc>)
else()
    list(APPEND LINK_DEPS ${SHADERC_LIBRARIES})
    set(INCLUDE_DEPS_DIR ${SHADERC_INCLUDE_DIRS})
endif()
