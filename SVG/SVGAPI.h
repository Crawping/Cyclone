/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once



#ifdef __linux__
    #define InternalAPI   __attribute__(visibility("hidden"))
	#if defined (SVG_EXPORTS)
        #define SVGAPI    __attribute__(visibility("default"))
    #else
        #define SVGAPI
    #endif
#else
    #define InternalAPI
    #if defined(SVG_EXPORTS)
        #define SVGAPI    __declspec(dllexport)
    #else
        #define SVGAPI    __declspec(dllimport)
    #endif
#endif
