#--------------------------------------------------------------------
# Source and Header Files
#--------------------------------------------------------------------
list(APPEND PUBLIC_HEADER_FILES
  ${INCLUDE_DIR}/vapi.h
  ${INCLUDE_DIR}/vutils.h
  ${INCLUDE_DIR}/vultra.h
)

list(APPEND PRIVATE_HEADER_FILES
  ${SOURCE_DIR}/vcore_context.h
)

list(APPEND SOURCE_FILES
  # Modules
  ${SOURCE_DIR}/vcore.c
  ${SOURCE_DIR}/vinput.c
  ${SOURCE_DIR}/vutils.c

  # Platforms
  ${SOURCE_DIR}/platforms/vcore_glfw.c
)

#--------------------------------------------------------------------
# Library Setup
#--------------------------------------------------------------------
add_library(${PROJECT_NAME}
    ${PUBLIC_HEADER_FILES}
    ${SOURCE_FILES}
    ${PRIVATE_HEADER_FILES}
)

#
# Vulkan
#
find_package(Vulkan QUIET)

if(NOT Vulkan_FOUND)
    message(STATUS "System Vulkan not found, using CPM to fetch Vulkan-Headers")

    CPMAddPackage(
        NAME VulkanHeaders
        GITHUB_REPOSITORY KhronosGroup/Vulkan-Headers
        GIT_TAG v1.4.325
        OPTIONS
            "BUILD_TESTS OFF"
    )

    # Create Vulkan::Headers target if it doesn't exist
    if(NOT TARGET Vulkan::Headers)
        add_library(Vulkan::Headers INTERFACE IMPORTED)
        target_include_directories(Vulkan::Headers INTERFACE
            ${VulkanHeaders_SOURCE_DIR}/include
        )
    endif()

    list(APPEND LINK_DEPS Vulkan::Headers)
else()
    list(APPEND LINK_DEPS Vulkan::Vulkan)
endif()

# Linux libs
if(UNIX AND NOT APPLE)
    list(APPEND LINK_DEPS PUBLIC
        ${CMAKE_DL_LIBS}  # Dynamic linking (libdl)
        pthread           # POSIX threads
        X11               # X Window System
        Xrandr            # RandR extension for monitor info
        Xi                # X Input extension
        Xxf86vm           # XFree86 video mode extension
        m                 # Math library
    )
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_DEPS})

# Set compile flags
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>>:-Weverything>
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -fdiagnostics-color=always>
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
)

#--------------------------------------------------------------------
# Include Directories
#--------------------------------------------------------------------
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${INCLUDE_DEPS_DIR}"
)

#--------------------------------------------------------------------
# Target Properties
#--------------------------------------------------------------------
set_target_properties(${PROJECT_NAME}
PROPERTIES
        PUBLIC_HEADER "${PUBLIC_HEADER_FILES}"
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        C_EXTENSIONS OFF
        C_STANDARD 99
        C_STANDARD_REQUIRED ON
)

#--------------------------------------------------------------------
# Compile definitions
#--------------------------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PUBLIC
    # Build Type
    $<$<CONFIG:Debug>:VUL_DEBUG>
    $<$<CONFIG:Release>:VUL_RELEASE>

    # Log/Debug
    $<$<BOOL:${LOG_SUPPORT}>:LOG_SUPPORT>
)

#--------------------------------------------------------------------
# Source Groups
#--------------------------------------------------------------------
GroupSourcesByFolder(${PROJECT_NAME})

