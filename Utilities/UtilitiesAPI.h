// CHANGELOG
// Written by Josh Grooms on 20160704

#pragma once



#ifdef __linux__
    #define InternalAPI         __attribute__(visibility("hidden"))
	#if defined (UTILITIES_EXPORTS)
        #define UtilitiesAPI    __attribute__(visibility("default"))
    #else
        #define UtilitiesAPI
    #endif
#else
    #define InternalAPI
    #if defined(UTILITIES_EXPORTS)
        #define UtilitiesAPI    __declspec(dllexport)
    #else
        #define UtilitiesAPI    __declspec(dllimport)
    #endif
#endif


