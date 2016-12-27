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
        template<typename T> class ICollectionIterator;

        template<typename T>
        class ICollection
        {
            public:
                /// <summary> Gets the total number of elements present in the collection. </summary>
                virtual uint Count()    const = 0;
                /// <summary> Gets whether the collection is currently empty. </summary>
                virtual bool IsEmpty()  const { return Count() == 0; }
                /// <summary> Destroys any resources that are specially allocated by the collection. </summary>
                virtual ~ICollection() { }



                /** OPERATORS **/
                //virtual ICollectionIterator<T>& begin() = 0;
                //virtual ICollectionIterator<T>& end()   = 0;

                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                /// <returns> A constant reference to the data element that resides at the inputted array index. </returns>
                /// <param name="idx"> The numeric index of the desired element within the collection. </param>
                virtual const T& operator ()(uint index) const = 0;


            protected:

                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                /// <returns> 
                ///     A constant pointer to the data element that resides at the inputted array index. 
                /// </returns>
                /// <param name="idx"> The numeric index of the desired element within the collection. </param>
                //virtual const T* Index(uint index) const = 0;
        };

        template<typename T>
        class ICollectionIterator
        {
            public:

                /** PROPERTIES **/
                virtual uint Index() const = 0;



                /** DESTRUCTOR **/
                virtual ~ICollectionIterator() { }



                /** OPERATORS **/
                virtual bool operator ==(const ICollectionIterator<T>& other)   const = 0;
                virtual bool operator !=(const ICollectionIterator<T>& other)   const { return !operator ==(other); }

                virtual const T& operator *()                                   const = 0;

                virtual ICollectionIterator& operator ++()                      = 0;
                virtual ICollectionIterator& operator ++(int)                   { return operator ++(); }

        };



        
    }
}