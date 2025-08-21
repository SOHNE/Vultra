/******************************* VULTRA *********************************
*
*                               LICENSE
* -----------------------------------------------------------------------
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

#ifndef VULTRA_VAPI_H
#define VULTRA_VAPI_H

#include "vultra/vexport.h"

#if defined( VULTRA_STATIC_DEFINE )
#    define VAPI
#else
#    if defined( _WIN32 ) || defined( __CYGWIN__ )
#        ifdef Vultra_EXPORTS
#            ifdef __GNUC__
#                define VAPI __attribute__( ( dllexport ) )
#            else
#                define VAPI __declspec( dllexport )
#            endif
#        else
#            ifdef __GNUC__
#                define VAPI __attribute__( ( dllimport ) )
#            else
#                define VAPI __declspec( dllimport )
#            endif
#        endif
#    else
#        if __GNUC__ >= 4
#            define VAPI __attribute__( ( visibility( "default" ) ) )
#        else
#            define VAPI
#        endif
#    endif
#endif

#endif // VULTRA_VAPI_H
