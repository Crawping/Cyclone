/* CHANGELOG
 * Written by Josh Grooms on 20170423
 */

#pragma once

#ifdef __linux__
    #define InternalAPI         __attribute__(visibility("hidden"))
	#if defined (REFLECTION_EXPORTS)
        #define ReflectionAPI    __attribute__(visibility("default"))
    #else
        #define ReflectionAPI
    #endif
#else
    #define InternalAPI
    #if defined(REFLECTION_EXPORTS)
        #define ReflectionAPI    __declspec(dllexport)
    #else
        #define ReflectionAPI    __declspec(dllimport)
    #endif
#endif