/* CHANGELOG
 * Written by Josh Grooms on 20160903
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"
#include "Interfaces/ICollection.h"


namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> An interface used to designate a collection as having array-like characteristics. </summary>
        /// <typeparam name="T"> The type name of the data elements held by a collection. </typeparam>
        template<typename T> 
        struct IArray : public virtual ICollection<T>
        {
            public:
                /** PROPERTIES **/
                /// <summary> Gets the number of dimensions of an array-like collection. </summary>
                virtual uint Rank()         const = 0;

                /** DESTRUCTOR **/
                /// <summary> Destroys any resources that are specially allocated by a collection. </summary>
                virtual ~IArray() { }
        };

    }
}