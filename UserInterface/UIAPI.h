/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once



#ifdef __linux__
    #define InternalAPI   __attribute__(visibility("hidden"))
	#if defined (UI_EXPORTS)
        #define UIAPI    __attribute__(visibility("default"))
    #else
        #define UIAPI
    #endif
#else
    #define InternalAPI
    #if defined(UI_EXPORTS)
        #define UIAPI    __declspec(dllexport)
    #else
        #define UIAPI    __declspec(dllimport)
    #endif
#endif