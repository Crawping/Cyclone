// CHANGELOG
// Written by Josh Grooms on 20160704

#pragma once



#ifdef __linux__
	#if defined (UTILITIES_EXPORTS)
        #define OpenGLAPI __attribute__(visibility("default"))
    #else
        #define OpenGLAPI 
	#endif
#else
    #if defined(OPENGL_EXPORTS)
        #define OpenGLAPI __declspec(dllexport)
    #else
        #define OpenGLAPI __declspec(dllimport)
    #endif    
#endif