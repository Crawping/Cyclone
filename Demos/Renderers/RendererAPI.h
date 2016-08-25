/* CHANGELOG
 * Written by Josh Grooms on 20160825
 */

#pragma once



#ifdef __linux__
    #define InternalAPI     __attribute__(visibility("hidden"))
	#ifdef RENDERERS_EXPORTS
        #define RendererAPI   __attribute__(visibility("default"))
    #else
        #define RendererAPI
	#endif
#else
    #define InternalAPI
    #ifdef RENDERERS_EXPORTS
        #define RendererAPI   __declspec(dllexport)
    #else
        #define RendererAPI   __declspec(dllimport)
    #endif
#endif