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

/* Version: YY.MINOR.MICRO */
#define VVUL_VERSION "25.0.0"

#include "vultra/vapi.h"

#include <stdlib.h> /* malloc(), free() */

//----------------------------------------------------------------------------------------------------------------------
// Module Defines and Macros
//----------------------------------------------------------------------------------------------------------------------
#ifndef VAPI
#    define VAPI
#endif

#ifndef INLINE
#    define INLINE inline
#endif

// C++ compatibility, preventing name mangling
#if defined( __cplusplus )
/* clang-format off */
#    define CXX_GUARD_START extern "C" {
#    define CXX_GUARD_END   }
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
    // ...
} vvulContext;

//----------------------------------------------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------------------------------------------

static vvulContext vState = {};

//----------------------------------------------------------------------------------------------------------------------
// Module Specific Functions Declarations
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Module Functions Declarations
//----------------------------------------------------------------------------------------------------------------------

//
CXX_GUARD_START
//

VAPI void vInit( int width, int height ); // Initialize Vulkan devices and states
VAPI void vClose( void );                 // Deinitialize Vulkan

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
vInit( int width, int height )
{
}

INLINE void
vClose( void )
{
}

#endif // VVUL_IMPLEMENTATION
#endif // !VVUL_H
