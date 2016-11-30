/* CHANGELOG
 * Written by Josh Grooms on 20161126
 */

#pragma once
#include "Collections/BST.h"



namespace Cyclone
{
    namespace Utilities
    {
        

        template<typename T> struct RegistryKey
        {
            public:
                int Index()     const { return Registry->IndexOf(_key); }
                int Key()       const { return _key; }

                RegistryKey() :
                    _key(-1),
                    Registry(nullptr)
                {

                }
                RegistryKey(int key, const BST<int, T>* registry) :
                    _key(key),
                    Registry(registry)
                {

                }
                RegistryKey(RegistryKey<T>&& other) : 
                    _key(other._key),
                    Registry(other.Registry)
                {
                    other._key = -1;
                    other.Registry = nullptr;
                }
                RegistryKey(const RegistryKey<T>& other) : 
                    _key(other._key),
                    Registry(other.Registry)
                {

                }

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
                int _key;
                const BST<int, T>* Registry;
        };


        template<typename T>
        class Registry : public ICollection<T>
        {
            public:
                
                /** PROPERTIES **/
                virtual uint Count()        const { return Data.Count(); }
                virtual List<T> Values()    const { return Data.Values(); }



                /** CONSTRUCTOR **/
                Registry() { }



                /** UTILITIES **/
                virtual void Clear()                                        { Data.Clear(); }
                virtual bool Contains(const RegistryKey<T>& key)            const { return Data.Contains(key.Key()); }
                virtual RegistryKey<T> Register(const T& value)
                {
                    int key = FindValue(value);
                    if (key < 0)
                    {
                        key = CreateKey();
                        Data.Insert(key, value);
                    }

                    return RegistryKey<T>(key, &Data);
                }
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
