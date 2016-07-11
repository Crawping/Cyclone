/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"
#include "GL/OpenGL.h"




/** FUNCTION POINTERS **/




namespace Cyclone
{
    namespace Platform
    {
        /** PUBLIC API FUNCTIONS **/
        PlatformAPI int cglLoadAPI();
        PlatformAPI void cglClearAPI();
    }
}
