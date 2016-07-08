/* CHANGELOG
 * Written by Josh Grooms on 20151022
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Console
        {
            UtilitiesAPI void Write(const string& msg);
            UtilitiesAPI void Write(const char* msg);
            UtilitiesAPI void WriteLine(const string& msg);
            UtilitiesAPI void WriteLine(const char* msg);
        }
    }
}
