/* CHANGELOG
 * Written by Josh Grooms on 20161221
 */

#pragma once
#include "Enumerator.h"
#include "Collections/Multiset.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents an ordered collection of unique data elements. </summary>
        template<typename T>
        class Set : public Multiset<T>
        {
            public:

                /** CONSTRUCTORS **/
                using Multiset::Multiset;



                /** UTILITIES **/
                /// <summary> Inserts a new data element into the set, if it isn't already stored. </summary>
                /// <param name="value"> A unique data element to be inserted into the set. </param>
                /// <remarks> This operation silently fails when attempting to insert multiple copies of elements. </remarks>
                void Insert(const T& value) override
                {
                    if (!Contains(value)) { Multiset<T>::Insert(value); }
                }
        };
    }
}
