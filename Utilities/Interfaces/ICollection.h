/* CHANGELOG
 * Written by Josh Grooms on 20160922
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T>
        class UtilitiesAPI ICollection
        {
            public:
                /// <summary> Gets the total number of elements present in a collection. </summary>
                virtual uint Count()    const = 0;
                /// <summary> Gets whether a collection is currently empty. </summary>
                virtual bool IsEmpty()  const { return Count() == 0; }
                /// <summary> Destroys any resources that are specially allocated by a collection. </summary>
                virtual ~ICollection() { }


                /** OPERATORS **/
                virtual ICollectionIterator<T>& begin() = 0;
                virtual ICollectionIterator<T>& end()   = 0;

            protected:

                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                /// <returns> 
                ///     A constant pointer to the data element that resides at the inputted array index. 
                /// </returns>
                /// <param name="idx"> The numeric index of the desired element within the collection. </param>
                virtual const T* Index(uint index) const = 0;
        };

        template<typename T>
        class UtilitiesAPI ICollectionIterator
        {
            public:

                virtual uint Index() const { return Index; }


                ICollectionIterator(const T* value, uint index) : 
                    Collection(collection),
                    Index(index)
                {

                }

                bool operator ==(const ICollectionIterator<T>& other)   const
                {
                    return (Index == other.Index) && (Collection == other.Collection);
                }
                bool operator !=(const ICollectionIterator<T>& other)   const { return !(*this == other); }

                T& operator *()
                {
                    return Collection
                }

                virtual ICollectionIterator<T>& operator ++()
                {
                    ++index;
                }

            protected:
                const ICollection<T>*   Collection;
                uint                    Index;            

        };



        
    }
}