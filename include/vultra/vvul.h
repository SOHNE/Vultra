/********************************* VVUL **********************************
 *
 * Module: vvul
 *
 *                            CONFIGURATIONS
 * ------------------------------------------------------------------------
 *
 *                               LICENSE
 * ------------------------------------------------------------------------
 * Copyright (c) 2025 SOHNE, Leandro Peres (@zschzen)
 *
 * This software is provided "as-is", without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use
 * of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including
 * commercial applications, and to alter it and redistribute it freely, subject to the
 * following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not claim that
 *      you wrote the original software. If you use this software in a product, an
 *      acknowledgment in the product documentation would be appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *      as being the original software.
 *
 *   3. This notice may not be removed or altered from any source distribution.
 *
 *************************************************************************/

#ifndef VVUL_H
#define VVUL_H

#include "vultra/vapi.h"
#include "vultra/vversion.h"

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strcmp(), strlen() */

#include <vulkan/vulkan.h>

//----------------------------------------------------------------------------------------------------------------------
// Module Defines and Macros
//----------------------------------------------------------------------------------------------------------------------
#define VULTRA_VK_VERSION VK_MAKE_VERSION( VULTRA_VERSION_MAJOR, VULTRA_VERSION_MINOR, VULTRA_VERSION_PATCH )

#ifndef VAPI
#    define VAPI
#endif

#ifndef INLINE
#    define INLINE inline
#endif

#ifndef VUL_ARRAYSIZE
#    define VUL_ARRAYSIZE( a ) ( (int)( sizeof( a ) / sizeof( *( a ) ) ) )
#endif

#ifndef UNUSED
#    define UNUSED( x ) (void)( x )
#endif

// C++ compatibility, preventing name mangling
#if defined( __cplusplus )
/* clang-format off */
#   define CXX_GUARD_START extern "C" {
#   define CXX_GUARD_END   }
/* clang-format on */
#else
#    define CXX_GUARD_START
#    define CXX_GUARD_END
#endif

/* Ensure TRACELOG macros */
#ifndef TRACELOG
#    define TRACELOG( level, ... ) ( (void)( 0 ) )
#    define TRACELOGD( ... )       ( (void)( 0 ) )
#endif // !TRACELOG

/* Custom memory allocators */
#ifndef VUL_MALLOC
#    define VUL_MALLOC( b ) malloc( b )
#endif
#ifndef VUL_CALLOC
#    define VUL_CALLOC( c, b ) calloc( ( c ), ( b ) )
#endif
#ifndef VUL_REALLOC
#    define VUL_REALLOC( p, b ) realloc( ( p ), ( b ) )
#endif
#ifndef VUL_FREE
#    define VUL_FREE( p ) free( p )
#endif

//----------------------------------------------------------------------------------------------------------------------
// Types & Structures Definitions
//----------------------------------------------------------------------------------------------------------------------

/* clang-format off */
#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
    #include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool) && !defined(VUL_BOOL_TYPE)
    // Boolean type
    typedef enum bool { false = 0, true = !false } bool;
#endif
/* clang-format on */

// Current vvul State and Configs
typedef struct vvulContext
{
    struct
    {
        VkInstance handle;

    } Instance;

} vvulContext;

//----------------------------------------------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------------------------------------------
static vvulContext vState = { 0 };

//----------------------------------------------------------------------------------------------------------------------
// Module Specific Functions Declarations
//----------------------------------------------------------------------------------------------------------------------
static INLINE const char * VkResultToStr( VkResult err );
static INLINE bool         vCreateInstance( const char ** requiredExtensions, uint32_t extensionCount );

//----------------------------------------------------------------------------------------------------------------------
// Module Functions Declarations
//----------------------------------------------------------------------------------------------------------------------

//
CXX_GUARD_START
//

VAPI void vInit( const char ** requiredExtensions, uint32_t extensionCount );
VAPI void vClose( void ); // Deinitialize Vulkan

//
CXX_GUARD_END
//

//**********************************************************************************************************************
//
// Module Implementation
//
//**********************************************************************************************************************
#ifdef VVUL_IMPLEMENTATION

INLINE void
vInit( const char ** requiredExtensions, uint32_t extensionCount )
{
    // Instance
    //----------------------------------------------------------
    if( !vCreateInstance( requiredExtensions, extensionCount ) ) return;
}

// Deinitializes and closes the Vulkan context
INLINE void
vClose( void )
{
    vkDestroyInstance( vState.Instance.handle, NULL );
}

//----------------------------------------------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------------------------------------------

static INLINE const char *
VkResultToStr( VkResult err )
{
    switch( err )
        {
#    define STR( R )                                                                                                   \
    case VK_##R: return #R
            STR( SUCCESS );
            STR( NOT_READY );
            STR( TIMEOUT );
            STR( EVENT_SET );
            STR( EVENT_RESET );
            STR( INCOMPLETE );
            STR( ERROR_OUT_OF_HOST_MEMORY );
            STR( ERROR_OUT_OF_DEVICE_MEMORY );
            STR( ERROR_INITIALIZATION_FAILED );
            STR( ERROR_DEVICE_LOST );
            STR( ERROR_MEMORY_MAP_FAILED );
            STR( ERROR_LAYER_NOT_PRESENT );
            STR( ERROR_EXTENSION_NOT_PRESENT );
            STR( ERROR_FEATURE_NOT_PRESENT );
            STR( ERROR_INCOMPATIBLE_DRIVER );
            STR( ERROR_TOO_MANY_OBJECTS );
            STR( ERROR_FORMAT_NOT_SUPPORTED );
            STR( ERROR_SURFACE_LOST_KHR );
            STR( SUBOPTIMAL_KHR );
            STR( ERROR_OUT_OF_DATE_KHR );
            STR( ERROR_INCOMPATIBLE_DISPLAY_KHR );
            STR( ERROR_NATIVE_WINDOW_IN_USE_KHR );
            STR( ERROR_VALIDATION_FAILED_EXT );
#    undef STR
        default: return "UNKNOWN_RESULT";
        }
}

// Create Vulkan instance
static INLINE bool
vCreateInstance( const char ** extensions, uint32_t extensionCount )
{
    VkApplicationInfo    appInfo    = { 0 };
    VkInstanceCreateInfo createInfo = { 0 };
    VkResult             result;

    // Application Info
    {
        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = "Vultra Application";
        appInfo.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 );
        appInfo.pEngineName        = "Vultra";
        appInfo.engineVersion      = VULTRA_VK_VERSION;
        appInfo.apiVersion         = VK_API_VERSION_1_0;
    }

    // Instance Create Info
    {
        createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo        = &appInfo;

        createInfo.enabledExtensionCount   = extensionCount;
        createInfo.ppEnabledExtensionNames = extensions;

        // TODO: Implement valiantion layers
        createInfo.enabledLayerCount       = 0;
        createInfo.ppEnabledLayerNames     = NULL;
    }

    result = vkCreateInstance( &createInfo, NULL, &vState.Instance.handle );
    if( VK_SUCCESS != result )
        {
            TRACELOG( LOG_FATAL, "VVUL: Failed to create Vulkan instance: %s", VkResultToStr( result ) );
            return false;
        }

    return true;
}

#endif // VVUL_IMPLEMENTATION
#endif // !VVUL_H
