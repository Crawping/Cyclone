/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once



#ifdef __linux__
    #define InternalAPI     __attribute__(visibility("hidden"))
    #ifdef PLATFORM_EXPORTS
        #define PlatformAPI __attribute__(visibility("default"))
    #else
        #define PlatformAPI
    #endif
#else
    #define InternalAPI
    #ifdef PLATFORM_EXPORTS
        #define PlatformAPI __declspec(dllexport)
    #else
        #define PlatformAPI __declspec(dllimport)
    #endif
#endif
