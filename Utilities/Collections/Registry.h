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
                int Index()     const { return Collection->IndexOf(_key); }
                int Key()       const { return _key; }

                RegistryKey(int key, const Registry<T>* collection) :
                    _key(key),
                    Collection(collection)
                {

                }


            private:
                int _key;
                const Registry<T>* Collection;
        };



        template<typename T>
        class Registry : public BST<RegistryKey<T>*, T>
        {

            public:

                ~Registry()
                {
                    for (auto* k : Keys())
                        delete k;
                }


                const RegistryKey<T>& Register(const T& value)
                {
                    uint idx = 0;
                    List<T> values = Values();
                    for (const T& v : values)
                        if (v == value)
                            return *(Keys()(idx));
                        else
                            idx++;

                    idx = 0;
                    List<RegistryKey<T>*> keys = Keys();
                    for (const auto* k : keys)
                        if (k->Key() == idx)
                            idx++
                        else
                        {
                            RegistryKey<T>* key = new RegistryKey<T>(idx, this);
                            Set(key, value);
                            return *key;
                        }

                    RegistryKey<T>* key = new RegistryKey<T>(++idx, this);
                    Set(key, value));
                    return *key;
                }




        };
    }
}
