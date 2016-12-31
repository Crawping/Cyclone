/* CHANGELOG
 * Written by Josh Grooms on 20161126
 */

#pragma once
#include "Collections/BST.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        /// <summary> A class that represents a specialized key used to index into a registry of data. </summary>
        template<typename T> struct RegistryKey
        {
            public:
                /// <summary> Gets the numeric index of the corresponding data element within the registry. </summary>
                int Index()     const { return Registry->IndexOf(_key); }
                /// <summary> Gets whether the key is valid for use. </summary>
                bool IsValid()  const { return (_key >= 0) && Registry; }
                /// <summary> Gets the integer key used to index into the registry's search tree. </summary>
                int Key()       const { return _key; }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new default null registry key. </summary>
                RegistryKey() :
                    _key(-1),
                    Registry(nullptr)
                {

                }
                /// <summary> Constructs a new registry key that corresponds with a particular value stored in a registry. </summary>
                /// <param name="key"> The integer key used to index into the registry's search tree. </param>
                /// <param name="registry"> The registry instance in which the value corresponding with the <paramref name="key"/> is stored. </param>
                RegistryKey(int key, const BST<int, T>* registry) :
                    _key(key),
                    Registry(registry)
                {

                }
                /// <summary> Constructs a new registry key containing the uncopied contents transferred from another key. </summary>
                /// <param name="other"> A pre-existing registry key whose contents are to be moved over into the new key. </param>
                RegistryKey(RegistryKey<T>&& other) : 
                    _key(other._key),
                    Registry(other.Registry)
                {
                    other._key = -1;
                    other.Registry = nullptr;
                }
                /// <summary> Constructs a new registry key that is an identical deep copy of another key. </summary>
                /// <param name="other"> A pre-existing registry key whose contents are to be copied into the new key. </param>
                RegistryKey(const RegistryKey<T>& other) : 
                    _key(other._key),
                    Registry(other.Registry)
                {

                }



                /** OPERATORS **/
                bool operator ==(const RegistryKey<T>& other) const
                {
                    return (Registry == other.Registry) && (Key() == other.Key());
                }
                bool operator !=(const RegistryKey<T>& other) const { return !(*this == other); }

                RegistryKey& operator =(RegistryKey<T>&& other)
                {
                    _key = other._key;
                    Registry = other.Registry;

                    other._key = -1;
                    other.Registry = nullptr;

                    return *this;
                }
                RegistryKey& operator =(const RegistryKey<T>& other)
                {
                    _key = other._key;
                    Registry = other.Registry;
                    return *this;
                }

            private:

                int                 _key;
                const BST<int, T>*  Registry;
        };



        /// <summary> A class that represents a collection of elements that are associated with automatically generated indexing keys. </summary>
        /// <typeparam name="T"> The type name of the data elements held by the registry. </typeparam>
        template<typename T>
        class Registry : public ICollection<T>
        {
            public:
                
                /** PROPERTIES **/
                /// <summary> Gets the number of data elements that stored within the registry. </summary>
                virtual uint Count()        const override { return Data.Count(); }
                /// <summary> Gets a list of all data elements stored within the registry. </summary>
                virtual List<T> Values()    const { return Data.Values(); }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new empty registry that can be populated with data elements. </summary>
                Registry() { }



                /** UTILITIES **/
                /// <summary> Removes all data elements stored within the registry. </summary>
                virtual void Clear()                                        { Data.Clear(); }
                /// <summary> Determines whether any data associated with a specific key is stored within the registry. </summary>
                /// <param name="key"> The specific key to be tested. </param>
                /// <returns> A Boolean <c>true</c> if the registry contains data associated with the inputted <paramref name="key"/>, or <c>false</c> otherwise. </returns>
                virtual bool Contains(const RegistryKey<T>& key)            const { return Data.Contains(key.Key()); }
                /// <summary> Inserts a new data element into the registry. </summary>
                /// <param name="value"> A new data element to be registered. </param>
                /// <returns> A special key unique to the inputted <paramref name="value"/> that can be used to index into the registry. </returns>
                virtual RegistryKey<T> Register(const T& value)
                {
                    int key = CreateKey();
                    Data.Insert(key, value);
                    return RegistryKey<T>(key, &Data);
                }
                /// <summary> Removes the data associated with a specific key from the registry. </summary>
                /// <param name="key"> A registry key for which any corresponding data should be removed. </param>
                virtual void Remove(const RegistryKey<T>& key)              { Data.Remove(key.Key()); }



                /** OPERATORS **/
                virtual T& operator [](const RegistryKey<T>& key)           { return Data[key.Key()]; }
                virtual const T& operator [](const RegistryKey<T>& key)     const { return Data[key.Key()]; }
                virtual const T& operator ()(uint index)                    const { return Data(index); }
                
            private:

                /** DATA **/
                BST<int, T>     Data;

                

                /** UTILITIES **/
                int CreateKey() const
                {
                    int key = 0;
                    while (Data.Contains(key)) { key++; }
                    return key;
                }
                int FindValue(const T& value) const
                {
                    int idx = 0;
                    auto values = Data.Values();
                    for (const T& v : values)
                        if (v == value) { return Data.Keys()(idx); }
                        else            { idx++; }

                    return -1;
                }                

        };

    }
}
