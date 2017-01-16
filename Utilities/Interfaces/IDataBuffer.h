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
        class IDataBuffer : public virtual IUpdatable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of individual elements that are stored within the buffer. </summary>
                virtual uint Count()        const = 0;
                /// <summary> Gets whether the buffer object is currently empty. </summary>
                /// <remarks> By default, this method determines whether the returned <see cref="Count"/> value is zero. </remarks>
                virtual bool IsEmpty()      const { return Count() == 0; }
                
                /** DESTRUCTOR **/
                virtual ~IDataBuffer() { }

                /** UTILITIES **/
                /// <summary> Removes all of the data stored within the buffer. </summary>
                virtual void Clear() = 0;
        };
    }
}
