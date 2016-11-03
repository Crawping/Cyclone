/* CHANGELOG
 * Written by Josh Grooms on 20161103
 */

#pragma once
#include "TypeDefinitions.h"
#include "Interfaces/IUpdatable.h"



namespace Cyclone
{
    namespace Utilities
    {
        class IDataBuffer : 
            public virtual IUpdatable
        {
            public:

                /** PROPERTIES **/
                virtual uint Count()        const = 0;
                virtual bool IsEmpty()      const { return Count() == 0; }


                virtual ~IDataBuffer() { }

        };
    }
}
