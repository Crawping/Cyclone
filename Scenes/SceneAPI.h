/* CHANGELOG
 * Written by Josh Grooms on 20170115
 */

#pragma once




#ifdef __linux__
    #define InternalAPI   __attribute__(visibility("hidden"))
	#if defined (SCENE_EXPORTS)
        #define SceneAPI    __attribute__(visibility("default"))
    #else
        #define SceneAPI
    #endif
#else
    #define InternalAPI
    #if defined(SCENE_EXPORTS)
        #define SceneAPI    __declspec(dllexport)
    #else
        #define SceneAPI    __declspec(dllimport)
    #endif
#endif
