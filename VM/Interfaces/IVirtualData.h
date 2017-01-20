/* CHANGELOG
 * Written by Josh Grooms on 20170119
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    using namespace Utilities;
    namespace VM
    {

        class IVirtualData
        {
            public:
                
                /** PROPERTIES **/
                virtual uint ID()           const = 0;



                /** DESTRUCTOR **/
                virtual ~IVirtualData() { }
        };
    }
}
