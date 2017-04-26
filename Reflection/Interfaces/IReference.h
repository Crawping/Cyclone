/* CHANGELOG
 * Written by Josh Grooms on 20171425
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;

        class IReference
        {
            public:
                
                virtual bool IsConstant()           const = 0;
                virtual bool IsReference()          const = 0;
                virtual bool IsPointer()            const = 0;
                virtual uint TypeID()               const = 0;
                virtual const string& TypeName()    const = 0;
                virtual uint Size()                 const = 0;

                virtual ~IReference() { }
        };
    }
}
