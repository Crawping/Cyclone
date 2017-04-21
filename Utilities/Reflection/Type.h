/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Utilities.h"
#include "Collections/Set.h"
#include "Reflection/MetaUtilities.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** FORWARD DECLARATIONS **/
        class Field;
        using namespace Utilities;


        /// <summary> A class that holds runtime-accessible information about other classes. </summary>
        class Metaclass
        {
            public:
                
                /** PROPERTIES **/    
                /// <summary> Gets the unique numeric identifier associated with the class. </summary>
                uint ID()               const { return _id; }
                /// <summary> Gets whether the class is of a reference type. </summary>
                bool IsReference()      const { return _isReference; }
                /// <summary> Gets whether the class if of a pointer type. </summary>
                bool IsPointer()        const { return _isPointer; }
                /// <summary> Gets the human-readable string name of the class. </summary>
                const string& Name()    const { return _name; }
                /// <summary> Gets the number of bytes required to store an instance of the class. </summary>
                uint Size()             const { return _size; }



                /** STATIC CONSTRUCTOR **/
                /// <summary> Constructs a new metaclass object containing information about a specific type. </summary>
                /// <typeparam name="T"> The type for which the metaclass is to be constructed. </typeparam>
                template<typename T> static Metaclass Create()
                {
                    const auto& type = typeid(Meta::Dereference<T>::Class);

                    Metaclass m;
                    m._id           = type.hash_code();
                    m._isPointer    = Meta::IsPointer<T>();
                    m._isReference  = Meta::IsReference<T>();
                    m._name         = type.name();
                    m._size         = Meta::SizeOf<T>();
                    
                    m.Register();
                    return m;
                }
                UtilitiesAPI ~Metaclass();



                /** UTILITIES **/
                /// <summary> Determines whether the class contains a specific field. </summary>
                /// <returns> A Boolean <c>true</c> if the field is part of the class description, or <c>false</c> otherwise. </returns>
                /// <param name="field"> A field object to be tested for inclusion in the class description. </param>
                UtilitiesAPI bool Contains(const Field& field) const;
                /// <summary> Adds a new field to the class description. </summary>
                /// <param name="type"> Another metaclass object that describes the type of the field being added. </param>
                /// <param name="name"> The human-readable string name of the field being added. </param>
                UtilitiesAPI void Insert(const Metaclass& type, const string& name);



                /** STATIC UTILITIES **/
                /// <summary> Gets the metaclass object that corresponds with the string name of the underlying type. </summary>
                UtilitiesAPI static const Metaclass& Get(const string& name);
                /// <summary> Determines whether a specific class has been registered with the reflection system. </summary>
                UtilitiesAPI static bool IsClass(const string& name);
                /// <summary> Determines whether a specific class has been registered with the reflection system. </summary>
                template<typename T> static bool IsClass()
                {
                    const auto& type = typeid(Meta::Dereference<T>::Class);
                    return IsClass(type.name());
                }

            private:
                
                /** DATA **/
                Set<Field*> _fields;
                uint        _id;
                bool        _isReference;
                bool        _isPointer;
                string      _name;
                uint        _size;



                /** CONSTRUCTOR **/
                UtilitiesAPI Metaclass();



                /** UTILITIES **/
                UtilitiesAPI void Register() const;

        };

    }
}
