/********************************* VCORE *********************************
 * vcore: Window management
 *
 *                           BACKEND PLATFORMS
 * ------------------------------------------------------------------------
 * DESKTOP:
 *     - GLFW (3.4)
 *
 *                                NOTES
 * ------------------------------------------------------------------------
 * WARN:
 *   - Early development stage
 *
 * TODO:
 *   - Expand backend support for additional platforms.
 *
 *                               LICENSE
 * ------------------------------------------------------------------------
 * Copyright (c) 2025 SOHNE, Leandro Peres (@zschzen)
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

#include "vultra/vultra.h"
#include "vultra/vutils.h"

#include "vcore_context.h"

#define VVUL_IMPLEMENTATION
#include "vultra/vvul.h"

//--------------------------------------------------------------------------------------------------------------
// GLOBALS
//--------------------------------------------------------------------------------------------------------------
CoreContext core = { 0 };

//--------------------------------------------------------------------------------------------------------------
// MODULE FUNCTIONS DECLARATIONS
//--------------------------------------------------------------------------------------------------------------
extern int  InitPlatform( void );
extern void ClosePlatform( void );

//--------------------------------------------------------------------------------------------------------------
// MODULE FUNCTIONS DEFINITONS
//--------------------------------------------------------------------------------------------------------------
void
InitWindow( int width, int height, const char * title )
{
    TRACELOG( LOG_INFO, "Initializing Vultra - %s", VULTRA_VERSION );

    // Initialize window data
    core.window.screen.height = (unsigned int)height;
    core.window.screen.width  = (unsigned int)width;
    if( STR_NONEMPTY( title ) )
        {
            core.window.title = title;
        }

    TRACELOG( LOG_INFO, "Initializing window: %s (%dx%d)", core.window.title, core.window.screen.width,
              core.window.screen.height );

    // Initialize platform
    //--------------------------------------------------------------
    if( 0 != InitPlatform() )
        {
            TRACELOG( LOG_WARNING, "SYSTEM: Failed to initialize Platform" );
            return;
        }
    //--------------------------------------------------------------

    vInit( core.window.screen.width, core.window.screen.height );

    TRACELOG( LOG_INFO, "Window initialized successfully" );
}

void
CloseWindow( void )
{
    ClosePlatform();

    TRACELOG( LOG_INFO, "Window closed" );
}

void
SetTargetFPS( int fps )
{
    if( fps < 1 )
        {
            core.timing.targetFPS = 0.0;
        }
    else
        {
            core.timing.targetFPS = 1.0 / (double)fps;
        }
}

void
SetConfigFlags( unsigned int flags )
{
    FLAG_SET( core.window.flags, flags );
}

void
BeginDrawing( void )
{
}

void
EndDrawing( void )
{
    core.timing.lastFrameTime = 0;
    ++core.timing.frameCounter;

    PollInputEvents();
}

void
ClearBackground( Color color )
{
    UNUSED( color );
    NO_IMPL();
}

float
GetFrameTime( void )
{
    NO_IMPL();
    return 0.0F;
}

int
GetFPS( void )
{
    NO_IMPL();
    return 0;
}
