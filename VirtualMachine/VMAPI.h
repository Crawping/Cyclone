/* CHANGELOG
 * Written by Josh Grooms on 20170118
 */

#pragma once

#ifdef __linux__
    #define InternalAPI   __attribute__(visibility("hidden"))
	#if defined (VM_EXPORTS)
        #define VMAPI    __attribute__(visibility("default"))
    #else
        #define VMAPI
    #endif
#else
    #define InternalAPI
    #if defined(VM_EXPORTS)
        #define VMAPI    __declspec(dllexport)
    #else
        #define VMAPI    __declspec(dllimport)
    #endif
#endif
