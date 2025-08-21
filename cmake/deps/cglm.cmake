find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(CGLM QUIET cglm)
endif()

if(NOT CGLM_FOUND)
    message(STATUS "System cglm not found, fetching using CPM")
    CPMAddPackage(
        NAME cglm
        GITHUB_REPOSITORY recp/cglm
        GIT_TAG v0.9.6
        OPTIONS
            "CGLM_SHARED ON"
            "CGLM_STATIC OFF"
            "CGLM_USE_C99 ON"
    )
    list(APPEND LINK_DEPS cglm)
else()
    list(APPEND LINK_DEPS ${CGLM_LIBRARIES})
    set(INCLUDE_DEPS_DIR ${CGLM_INCLUDE_DIRS})
endif()

