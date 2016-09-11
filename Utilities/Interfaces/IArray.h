/* CHANGELOG
 * Written by Josh Grooms on 20160903
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {
        template<typename T>
        struct IArray
        {
            public:
                /// <summary> Gets the total number of elements present in an array-like collection. </summary>
                virtual uint Count()        const = 0;
                /// <summary> Gets whether an array-like collection is currently empty. </summary>
                virtual bool IsEmpty()      const { return Count() == 0; }
                /// <summary> Gets the number of dimensions of an array-like collection. </summary>
                virtual uint Rank()         const = 0;


                virtual ~IArray() { }
                
                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                virtual const T& operator ()(uint idx) const = 0;
        };

    }
}