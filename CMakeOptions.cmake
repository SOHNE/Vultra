include(CMakeDependentOption)
include(EnumOption)

#--------------------------------------------------------------------
# Define Enum Options
#--------------------------------------------------------------------
enum_option(WINDOW_SYSTEM "GLFW;" "Select the windowing system to use.")

#--------------------------------------------------------------------
# Build Options
#--------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build Vultra as a shared library" OFF)

option(USE_CCACHE "Enable compiler cache that can drastically improve build times" ${IS_MAIN})
option(CCACHE_OPTIONS "Compiler cache options" "CCACHE_CPP2=true;CCACHE_SLOPPINESS=clang_index_store")

option(LOG_SUPPORT "Enable Vultra logging system" ON)

#--------------------------------------------------------------------
# Sanitize Options
#--------------------------------------------------------------------
option(SANITIZE_ADDRESS "Enable Address sanitizer" OFF)
option(SANITIZE_MEMORY "Enable Memory sanitizer" OFF)
option(SANITIZE_THREAD "Enable Thread sanitizer" OFF)
option(SANITIZE_UNDEFINED "Enable Undefined Behavior sanitizer" OFF)
option(SANITIZE_LINK_STATIC "Link sanitizers statically (for gcc)" OFF)
