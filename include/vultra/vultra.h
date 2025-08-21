/******************************** VULTRA *********************************
*
* Version:    v25.0.0                  Author: Leandro Peres <leandro@peres.dev>
* Released:   2025-08-20               License: zlib/libpng (OSI Approved)
*
* A minimal vulkan graphics library designed for:
* - Educational purposes & computer graphics fundamentals
* - C99 development workflows
*
*                               LICENSE
* ------------------------------------------------------------------------
* Copyright (c) 2025 SOHNE, Leandro Peres <leandro@peres.dev>
*
* This software is provided "as-is", without any express or implied warranty. In no event
* will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you
*   wrote the original software. If you use this software in a product, an acknowledgment
*   in the product documentation would be appreciated but is not required.
*
*   2. Altered source versions must be plainly marked as such, and must not be misrepresented
*   as being the original software.
*
*   3. This notice may not be removed or altered from any source distribution.
*
*************************************************************************/

#ifndef VULTRA_H
#define VULTRA_H

//==============================================================================================================
// INCLUDES
//==============================================================================================================
#include "vultra/vapi.h"
#include "vultra/vversion.h"

#include <stdarg.h> /* va_list */
#include <stddef.h>
#include <stdlib.h>

//==============================================================================================================
// DEFINES
//==============================================================================================================
#ifndef VAPI
#    define VAPI
#endif

/// Compiler attributes
#if defined( __GNUC__ ) || defined( __clang__ )
#    define NORETURN      __attribute__( ( noreturn ) )
#    define PACKED        __attribute__( ( packed ) )
#    define INLINE        inline __attribute__( ( always_inline ) )
#    define ALIGNED( x )  __attribute__( ( aligned( x ) ) ) // Align variables/structs
#    define DEPRECATED    __attribute__( ( deprecated ) )   // Mark as deprecated
#    define LIKELY( x )   __builtin_expect( !!( x ), 1 )    // Branch prediction hint
#    define UNLIKELY( x ) __builtin_expect( !!( x ), 0 )
#elif defined( _MSC_VER )
#    define NORETURN      __declspec( noreturn )
#    define PACKED        __pragma( pack( push, 1 ) )
#    define INLINE        __forceinline
#    define ALIGNED( x )  __declspec( align( x ) )
#    define DEPRECATED    __declspec( deprecated )
#    define LIKELY( x )   ( x )
#    define UNLIKELY( x ) ( x )
#else
#    define NORETURN
#    define PACKED
#    define INLINE inline
#    define ALIGNED( x )
#    define DEPRECATED
#    define LIKELY( x )   ( x )
#    define UNLIKELY( x ) ( x )
#endif

// Custom memory allocators
#ifndef VUL_MALLOC
#    define VUL_MALLOC( sz ) malloc( sz )
#endif
#ifndef VUL_CALLOC
#    define VUL_CALLOC( n, sz ) calloc( n, sz )
#endif
#ifndef VUL_REALLOC
#    define VUL_REALLOC( ptr, sz ) realloc( ptr, sz )
#endif
#ifndef VUL_FREE
#    define VUL_FREE( ptr ) free( ptr )
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

// Boolean
#if !defined( __cplusplus ) && !defined( bool )
#    if defined( __has_include ) && __has_include( <stdbool.h> )
#        include <stdbool.h>
#    else
#        ifndef VULTRA_BOOL_TYPE
typedef enum bool
{
    false = 0,
    true  = !false
} bool;
#            define VULTRA_BOOL_TYPE
#        endif
#    endif
#endif

// Flags operations
#define FLAG_SET( n, f )    ( ( n ) |= ( f ) )
#define FLAG_CLEAR( n, f )  ( ( n ) &= ~( f ) )
#define FLAG_TOGGLE( n, f ) ( ( n ) ^= ( f ) )
#define FLAG_CHECK( n, f )  ( ( n ) & ( f ) )

// Determines if the given string is non null and non empty
#define STR_NONEMPTY( str ) ( ( str ) != NULL && ( str )[0] != '\0' )

// Unused variable
#define UNUSED( x )         (void)( x )

// Not implemented fatal error
#define NO_IMPL()           TRACELOG( LOG_FATAL, "Not implemented: %s (%s:%d)", __func__, __FILE__, __LINE__ )

//==============================================================================================================
// STRUCTS
//==============================================================================================================

// Color
typedef struct Color
{
    float r;
    float g;
    float b;
    float a;
} Color;

//===========================================================================================================
// ENUMERATORS
//===========================================================================================================
typedef enum
{
    FLAG_NONE             = 0,
    FLAG_VSYNC_HINT       = 1 << 0, // 0x01: Enable vertical sync
    FLAG_WINDOW_RESIZABLE = 1 << 1, // 0x02: Allow window resizing
    FLAG_MSAA_HINT        = 1 << 2  // 0x04: Enable MSAA (Multi-Sample Anti-Aliasing)
} ConfigFlags;

// Log levels
typedef enum
{
    LOG_ALL = 0, // Display all logs
    LOG_TRACE,   // Trace logging, intended for internal use only
    LOG_DEBUG,   // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,    // Info logging, used for program execution info
    LOG_WARNING, // Warning logging, used on recoverable failures
    LOG_ERROR,   // Error logging, used on unrecoverable failures
    LOG_FATAL,   // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE     // Disable logging
} LogLevel;

// Keyboard keys
typedef enum
{
    KEY_NULL          = 0, // No key pressed

    // Char Keys
    KEY_SPACE         = 32, // Space
    KEY_APOSTROPHE    = 39, // '
    KEY_COMMA         = 44, // ,
    KEY_MINUS         = 45, // -
    KEY_PERIOD        = 46, // .
    KEY_SLASH         = 47, // /
    KEY_ZERO          = 48, // 0
    KEY_ONE           = 49, // 1
    KEY_TWO           = 50, // 2
    KEY_THREE         = 51, // 3
    KEY_FOUR          = 52, // 4
    KEY_FIVE          = 53, // 5
    KEY_SIX           = 54, // 6
    KEY_SEVEN         = 55, // 7
    KEY_EIGHT         = 56, // 8
    KEY_NINE          = 57, // 9
    KEY_SEMICOLON     = 59, // ;
    KEY_EQUAL         = 61, // =
    KEY_A             = 65, // A - a
    KEY_B             = 66, // B - b
    KEY_C             = 67, // C - c
    KEY_D             = 68, // D - d
    KEY_E             = 69, // E - e
    KEY_F             = 70, // F - f
    KEY_G             = 71, // G - g
    KEY_H             = 72, // H - h
    KEY_I             = 73, // I - i
    KEY_J             = 74, // J - j
    KEY_K             = 75, // K - k
    KEY_L             = 76, // L - l
    KEY_M             = 77, // M - m
    KEY_N             = 78, // N - n
    KEY_O             = 79, // O - o
    KEY_P             = 80, // P - p
    KEY_Q             = 81, // Q - q
    KEY_R             = 82, // R - r
    KEY_S             = 83, // S - s
    KEY_T             = 84, // T - t
    KEY_U             = 85, // U - u
    KEY_V             = 86, // V - v
    KEY_W             = 87, // W - w
    KEY_X             = 88, // X - x
    KEY_Y             = 89, // Y - y
    KEY_Z             = 90, // Z - z
    KEY_LEFT_BRACKET  = 91, // [
    KEY_BACKSLASH     = 92, // '\'
    KEY_RIGHT_BRACKET = 93, // ]
    KEY_GRAVE         = 96, // `

    // System Keys
    KEY_ESCAPE        = 256, // Escape
    KEY_ENTER         = 257, // Enter
    KEY_TAB           = 258, // Tab
    KEY_BACKSPACE     = 259, // Backspace
    KEY_INSERT        = 260, // Insert
    KEY_DELETE        = 261, // Delete

    // Navigation Keys
    KEY_RIGHT         = 262, // Arrow Right
    KEY_LEFT          = 263, // Arrow Left
    KEY_DOWN          = 264, // Arrow Down
    KEY_UP            = 265, // Arrow Up
    KEY_PAGE_UP       = 266, // Page Up
    KEY_PAGE_DOWN     = 267, // Page Down
    KEY_HOME          = 268, // Home
    KEY_END           = 269, // End

    // Lock Keys
    KEY_CAPS_LOCK     = 280, // Caps Lock
    KEY_SCROLL_LOCK   = 281, // Scroll Lock
    KEY_NUM_LOCK      = 282, // Num Lock

    // Miscellaneous System Keys
    KEY_PRINT_SCREEN  = 283, // Print Screen
    KEY_PAUSE         = 284, // Pause

    // Function Keys
    KEY_F1            = 290, // F1
    KEY_F2            = 291, // F2
    KEY_F3            = 292, // F3
    KEY_F4            = 293, // F4
    KEY_F5            = 294, // F5
    KEY_F6            = 295, // F6
    KEY_F7            = 296, // F7
    KEY_F8            = 297, // F8
    KEY_F9            = 298, // F9
    KEY_F10           = 299, // F10
    KEY_F11           = 300, // F11
    KEY_F12           = 301, // F12

    // Modifier Keys
    KEY_LEFT_SHIFT    = 340, // Left Shift
    KEY_LEFT_CONTROL  = 341, // Left Control
    KEY_LEFT_ALT      = 342, // Left Alt
    KEY_LEFT_SUPER    = 343, // Left Super
    KEY_RIGHT_SHIFT   = 344, // Right Shift
    KEY_RIGHT_CONTROL = 345, // Right Control
    KEY_RIGHT_ALT     = 346, // Right Alt
    KEY_RIGHT_SUPER   = 347, // Right Super
    KEY_KB_MENU       = 348, // Keyboard Menu

    // Numpad Keys
    KEY_NUM_0         = 320, // 0
    KEY_NUM_1         = 321, // 1
    KEY_NUM_2         = 322, // 2
    KEY_NUM_3         = 323, // 3
    KEY_NUM_4         = 324, // 4
    KEY_NUM_5         = 325, // 5
    KEY_NUM_6         = 326, // 6
    KEY_NUM_7         = 327, // 7
    KEY_NUM_8         = 328, // 8
    KEY_NUM_9         = 329, // 9
    KEY_NUM_DOT       = 330, // .
    KEY_NUM_SLASH     = 331, // /
    KEY_NUM_MUL       = 332, // *
    KEY_NUM_MINUS     = 333, // -
    KEY_NUM_PLUS      = 334, // +
    KEY_NUM_ENTER     = 335, // Enter
    KEY_NUM_EQUAL     = 336, // =
} KeyboardCode;

//===========================================================================================================
// Functions callbacks
//===========================================================================================================

// Custom trace log
typedef void ( *TraceLogCallback )( int logLevel, const char * text, va_list args );

//===========================================================================================================
// FUNCTIONS DECLARATIONS
//===========================================================================================================

CXX_GUARD_START

//--- CORE --------------------------------------------------------------------------------------------------

// Window
VAPI void   InitWindow( int width, int height, const char * title );
VAPI void   CloseWindow( void );
VAPI void   SetWindowTitle( const char * title );
VAPI bool   ShouldQuit( void );
VAPI void * GetWindowHandle( void );
VAPI void   SignalClose( void );

// Timing functions
VAPI void   SetTargetFPS( int fps );
VAPI float  GetFrameTime( void );
VAPI double GetTime( void );
VAPI int    GetFPS( void );

// Drawing functions
VAPI void BeginDrawing( void );
VAPI void EndDrawing( void );

// Miscellaneous core functions
VAPI void SetTraceLogCallback( TraceLogCallback callback ); // Set custom trace log
VAPI void TraceLog( int logLevel, const char * text, ... ); // Display a log message

VAPI void PollInputEvents( void );

//--- INPUT -------------------------------------------------------------------------------------------------

VAPI bool IsAnyKeyPressed( void );         // Check if any key is been pressed
VAPI bool IsKeyPressed( int key );         // Check if the given key is been pressed
VAPI bool IsKeyPressedRepeated( int key ); // Check if the given key is repeated across frames
VAPI bool IsKeyDown( int key );            // Check if the given key is being pressed
VAPI bool IsKeyReleased( int key );        // Check if the given key has been released once
VAPI bool IsKeyUp( int key );              // Check if the key is NOT being pressed

CXX_GUARD_END

#endif // VULTRA_H
