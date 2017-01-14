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
                //virtual Iterator begin() = 0;
                //virtual Iterator end()   = 0;

                /// <summary> Performs linear indexing of the elements of an array-like collection. </summary>
                /// <returns> A constant reference to the data element that resides at the inputted array index. </returns>
                /// <param name="idx"> The numeric index of the desired element within the collection. </param>
                virtual const T& operator ()(uint index) const = 0;

            protected:

                struct Iterator
                {
                    public:

                        /** PROPERTIES **/
                        virtual uint Index() const { return _index; }



                        /** DESTRUCTOR **/
                        Iterator(uint index, ICollection<T>* collection) :
                            _index(index),
                            Collection(collection)
                        {

                        }
                        virtual ~Iterator() { }



                        /** OPERATORS **/
                        virtual const T& operator *()                       const { return (*Collection)(Index()); }
                        virtual Iterator& operator ++()                     { _index++; return *this; }
                        virtual Iterator& operator ++(int)                  { return operator ++(); }

                        virtual bool operator ==(const Iterator& other)     const
                        {
                            return (Index() == other.Index()) && (Collection == other.Collection);
                        }
                        virtual bool operator !=(const Iterator& other)     const { return !operator ==(other); }

                    private:

                        uint            _index;
                        ICollection<T>* Collection;

                };

        };
        
    }
}