/*******************************************************************************************
*
*   Vultra Core Example - Basic Window
*
*   Initially created with Vultra v25.0.0
*
*   Demonstrates the basic setup and usage of Vultra for window creation and rendering.
*
*   Licensed under the zlib/libpng license.
*   Copyright (c) 2025 SOHNE, Leandro Peres (@zschzen)
*
********************************************************************************************/

#include "vultra/vultra.h"

int
main( void )
{
    const int screenWidth  = 640;
    const int screenHeight = 480;

    InitWindow( screenWidth, screenHeight, "Vultra: Basic Window" );
    SetTargetFPS( 60 );

    while( !ShouldQuit() )
        {
            if( IsKeyDown( KEY_ESCAPE ) ) SignalClose();

            BeginDrawing();
            {
                // ...
            }
            EndDrawing();
        }

    CloseWindow();
    return EXIT_SUCCESS;
}
