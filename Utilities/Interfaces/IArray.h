/* CHANGELOG
 * Written by Josh Grooms on 20160903
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> An interface used to designate a collection as having array-like characteristics. </summary>
        /// <typeparam name="T"> The type name of the data elements held by a collection. </typeparam>
        template<typename T> struct IArray
        {
            public:
                /** PROPERTIES **/
                /// <summary> Gets the total number of elements present in an array-like collection. </summary>
                virtual uint Count()        const = 0;
                /// <summary> Gets whether an array-like collection is currently empty. </summary>
                virtual bool IsEmpty()      const { return Count() == 0; }
                /// <summary> Gets the number of dimensions of an array-like collection. </summary>
                virtual uint Rank()         const = 0;

                /** DESTRUCTOR **/
                /// <summary> Destroys any resources that are specially allocated by a collection. </summary>
                virtual ~IArray() { }

                /** OPERATORS**/
                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                /// <returns> A constant reference to the data element that resides at the inputted array index. </returns>
                virtual const T& operator ()(uint idx) const = 0;
        };

    }
}