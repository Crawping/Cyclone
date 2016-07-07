/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "OpenGL.h"



/** FUNCTION POINTERS **/
#ifdef __linux__
    #include "Linux/GLX.h"
#else
    #include "Windows/WGL.h"
#endif



/** PUBLIC API FUNCTIONS **/
int cglLoadFunctions();