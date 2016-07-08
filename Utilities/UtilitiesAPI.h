// CHANGELOG
// Written by Josh Grooms on 20160704

#pragma once



#ifdef __linux__
	#if defined (UTILITIES_EXPORTS)
        #define UtilitiesAPI __attribute__(visibility("default"))
    #else
        #define UtilitiesAPI
    #endif
#else
    #if defined(UTILITIES_EXPORTS)
        #define UtilitiesAPI __declspec(dllexport)
    #else
        #define UtilitiesAPI __declspec(dllimport)
    #endif
#endif


