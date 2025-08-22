#include "vcore_context.h"

#include "vultra/vultra.h"
#include "vultra/vutils.h"

#include <stddef.h>
#include <string.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

//--------------------------------------------------------------------------------------------------------------
// TYPES
//--------------------------------------------------------------------------------------------------------------
typedef struct PlatformContext
{
    GLFWwindow * handle;
} PlatformContext;

//--------------------------------------------------------------------------------------------------------------
// GLOBALS
//--------------------------------------------------------------------------------------------------------------
extern CoreContext     core;
static PlatformContext platform = { 0 };

//--------------------------------------------------------------------------------------------------------------
// MODULE FUNCTIONS DECLARATIONS
//--------------------------------------------------------------------------------------------------------------

// Platform
int  InitPlatform( void );
void ClosePlatform( void );

// Get all the required extensions for Vulkan instance
const char ** ExtensionCallback( uint32_t * count );

extern void SignalClose( void );

// Getters
int GetScreenWidth( void );
int GetScreenHeight( void );

// GLFW callbacks and window management
static void ErrorCallback( int error, const char * description );
static void FramebufferSizeCallback( GLFWwindow * window, int width, int height );
static void KeyCallback( GLFWwindow * window, int key, int scancode, int action, int mods );
static void WindowPosCallback( GLFWwindow * window, int x, int y );

// Wrappers used by glfwInitAllocator
static void * AllocateWrapper( size_t size, void * user );
static void * ReallocateWrapper( void * block, size_t size, void * user );
static void   DeallocateWrapper( void * block, void * user );

//----------------------------------------------------------------------------------
// Module Internal Functions Definition
//----------------------------------------------------------------------------------

static void *
AllocateWrapper( size_t size, void * user )
{
    UNUSED( user );
    return (void *)( VUL_MALLOC( size ) );
}

static void *
ReallocateWrapper( void * block, size_t size, void * user )
{
    UNUSED( user );
    return (void *)( VUL_REALLOC( block, size ) );
}

static void
DeallocateWrapper( void * block, void * user )
{
    UNUSED( user );
    VUL_FREE( block );
}

//--------------------------------------------------------------------------------------------------------------
// MODULE FUNCTIONS DEFINITIONS
//--------------------------------------------------------------------------------------------------------------
int
InitPlatform( void )
{
    // Init
    //----------------------------------------------------------------------------
    glfwSetErrorCallback( ErrorCallback );

    const GLFWallocator allocator = {
        .allocate   = AllocateWrapper,
        .deallocate = DeallocateWrapper,
        .reallocate = ReallocateWrapper,
        .user       = NULL,
    };

    glfwInitAllocator( &allocator );

#if defined( __APPLE__ )
    // Disable Resources folder working directory change on macOS
    glfwInitHint( GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE );
#endif

    if( GLFW_FALSE == glfwInit() )
        {
            TRACELOG( LOG_ERROR, "GLFW: Failed to initialize" );
            return -1;
        }

    // Hints
    //----------------------------------------------------------------------------
    glfwDefaultWindowHints();
    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, FLAG_CHECK( core.window.flags, FLAG_WINDOW_RESIZABLE ) ? GLFW_TRUE : GLFW_FALSE );
    glfwWindowHint( GLFW_AUTO_ICONIFY, 0 );

    platform.handle = glfwCreateWindow( (int)core.window.screen.width, (int)core.window.screen.height,
                                        core.window.title, NULL, NULL );

    if( !platform.handle )
        {
            glfwTerminate();
            TRACELOG( LOG_ERROR, "GLFW: Failed to create GLFW window" );
            return -1;
        }

    // Vulkan
    //----------------------------------------------------------------------------
    if( GLFW_FALSE == glfwVulkanSupported() )
        {
            TRACELOG( LOG_ERROR, "GLFW: Vulkan is not supported on this system" );
            glfwDestroyWindow( platform.handle );
            glfwTerminate();
            return -1;
        }

    // Callbacks
    //----------------------------------------------------------------------------
    glfwSetFramebufferSizeCallback( platform.handle, FramebufferSizeCallback );
    glfwSetKeyCallback( platform.handle, KeyCallback );
    glfwSetWindowPosCallback( platform.handle, WindowPosCallback );

    TRACELOG( LOG_INFO, "GLFW: %s", glfwGetVersionString() );

    return 0;
}

INLINE void
ClosePlatform( void )
{
    glfwDestroyWindow( platform.handle );
    glfwTerminate();
}

INLINE void
SignalClose( void )
{
    glfwSetWindowShouldClose( platform.handle, GLFW_TRUE );
}

// Get all the required extensions for Vulkan instance
const char **
ExtensionCallback( uint32_t * count )
{
    return glfwGetRequiredInstanceExtensions( count );
}

INLINE bool
ShouldQuit( void )
{
    return (bool)( core.window.shouldQuit );
}

INLINE void
SetWindowTitle( const char * title )
{
    core.window.title = title;
    glfwSetWindowTitle( platform.handle, title );
}

void
SwapBuffers( void )
{
}

void
WaitTime( double seconds )
{
    UNUSED( seconds );
}

// Window size getters
int
GetScreenWidth( void )
{
    int width, height;
    glfwGetFramebufferSize( platform.handle, &width, &height );
    return width;
}

int
GetScreenHeight( void )
{
    int width, height;
    glfwGetFramebufferSize( platform.handle, &width, &height );
    return height;
}

void *
GetWindowHandle( void )
{
    return (void *)platform.handle;
}

static void
ErrorCallback( int error, const char * description )
{
    TRACELOG( LOG_WARNING, "GLFW: Error: %i Description: %s", error, description );
}

static void
FramebufferSizeCallback( GLFWwindow * window, int width, int height )
{
    UNUSED( window );

    if( ( 0 == width ) || ( 0 == height ) ) return;

    core.window.screen.width  = (unsigned int)width;
    core.window.screen.height = (unsigned int)height;

    TRACELOG( LOG_INFO, "Window resized to %dx%d", width, height );
}

static void
WindowPosCallback( GLFWwindow * window, int x, int y )
{
    UNUSED( window );

    // Set current window position
    core.window.position.x = x;
    core.window.position.y = y;
}

static void
KeyCallback( GLFWwindow * window, int key, int scancode, int action, int mods )
{
    UNUSED( window );
    UNUSED( scancode );

    // Filter invalid key codes
    if( UNLIKELY( KEY_NULL > key ) ) return;

    switch( action )
        {
        case GLFW_RELEASE:
            {
                // Clear key state immediately on release
                core.input.keyboard.currKeyState[key] = 0;
                break;
            }
        case GLFW_PRESS:
            {
                // Update state and record press event
                core.input.keyboard.currKeyState[key] = 1;
                ++core.input.keyboard.pressedKeyCount;
                break;
            }
        case GLFW_REPEAT:
            {
                // Track sustained key repeats
                core.input.keyboard.keyRepeats[key] = 1;
                break;
            }
        default: break;
        }

    // Force lock keys to active state when modifiers match
    if( ( KEY_CAPS_LOCK == key && ( mods & GLFW_MOD_CAPS_LOCK ) )
        || ( KEY_NUM_LOCK == key && ( mods & GLFW_MOD_NUM_LOCK ) ) )
        {
            core.input.keyboard.currKeyState[key] = 1;
        }
}

void
PollInputEvents( void )
{
    /* Store previous states */
    for( size_t i = 0; i < KEYBOARD_KEY_COUNT; ++i )
        {
            core.input.keyboard.prevKeyState[i] = core.input.keyboard.currKeyState[i];
            core.input.keyboard.keyRepeats[i]   = 0;
        }

    /* Clear states */
    core.input.keyboard.pressedKeyCount = 0;

    /* Poll events */
    glfwPollEvents();

    /* Handle quit event */
    core.window.shouldQuit = glfwWindowShouldClose( platform.handle );
    glfwSetWindowShouldClose( platform.handle, GLFW_FALSE );
}
