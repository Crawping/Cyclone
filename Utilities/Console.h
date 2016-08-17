/* CHANGELOG
 * Written by Josh Grooms on 20151022
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



 /// <summary> A shortcut for posting status and debugging messages to the console window. </summary>
#define PostInfo(msg) \
    Cyclone::Utilities::Console::PostGeneralInfo(__FILE__, __LINE__, (msg));



namespace Cyclone
{
    namespace Utilities
    {
        namespace Console
        {
            /// <summary> Writes a string of text to the console window. </summary>
            UtilitiesAPI void Write(const string& msg);
            /// <summary> Writes a string of text to the console window. </summary>
            UtilitiesAPI void Write(const char* msg);
            /// <summary> Writes a string of text to the console window and starts a new line after it. </summary>
            UtilitiesAPI void WriteLine(const string& msg);
            /// <summary> Writes a string of text to the console window and starts a new line after it. </summary>
            UtilitiesAPI void WriteLine(const char* msg);

            /// <summary> Write a line of text to the console that is prepended with source code debugging information. </summary>
            UtilitiesAPI void PostGeneralInfo(const string& file, int line, const string& msg);
        }
    }
}
