/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Utilities.h"
#include "ReflectionAPI.h"
#include "Collections/Set.h"
#include "IO/Functions.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Reflection
    {

        /** FORWARD DECLARATIONS **/
        class Field;
        class Metaclass;


        namespace Meta
        {
            /// <summary> Gets a class object that encapsulates the type of the input argument. </summary>
            /// <returns> A templated class object representing the type of the inputted value. </returns>
            /// <param name="value"> An instance of the class whose type is to be found. </param>
            template<typename T> 
            const Metaclass& TypeOf(T value)                  { return Metaclass::Get<T>(); }
        }




        /// <summary> A class that holds runtime-accessible information about other classes. </summary>
        class Metaclass
        {
            public:
                
                /** PROPERTIES **/    
                uint CoreSize()         const { return _coreSize; }
                /// <summary> Gets the unique numeric identifier associated with the class. </summary>
                uint ID()               const { return _id; }
                /// <summary> Gets whether the class is constant qualified. </summary>
                bool IsConstant()       const { return _isConstant; }
                /// <summary> Gets whether the class represents a native C++ reference to a type. </summary>
                bool IsReference()      const { return _isReference; }
                /// <summary> Gets whether the class represents a native C++ pointer to a type. </summary>
                bool IsPointer()        const { return _isPointer; }
                /// <summary> Gets the human-readable string name of the class. </summary>
                const string& Name()    const { return _name; }
                /// <summary> Gets the number of bytes required to store an instance of the class. </summary>
                uint Size()             const { return _size; }



                /** CONSTRUCTORS & DESTRUCTOR **/
                Metaclass(const Metaclass& other) = delete;
                ReflectionAPI Metaclass(Metaclass&& other) noexcept;
                ReflectionAPI ~Metaclass();



                /** UTILITIES **/
                /// <summary> Determines whether the class contains a specific field. </summary>
                /// <returns> A Boolean <c>true</c> if the field is part of the class description, or <c>false</c> otherwise. </returns>
                /// <param name="field"> A field object to be tested for inclusion in the class description. </param>
                ReflectionAPI bool Contains(const Field& field) const;
                /// <summary> Adds a new field to the class description. </summary>
                /// <param name="type"> Another metaclass object that describes the type of the field being added. </param>
                /// <param name="name"> The human-readable string name of the field being added. </param>
                ReflectionAPI void Insert(const Metaclass& type, const string& name);



                /** STATIC UTILITIES **/
                /// <summary> Gets the metaclass object that corresponds with the name of the underlying type. </summary>
                ReflectionAPI static const Metaclass& Get(const string& name);
                /// <summary> Determines whether a specific class has been registered with the reflection system. </summary>
                ReflectionAPI static bool IsClass(const string& name);
                /// <summary> Determines whether a specific class has been registered with the reflection system. </summary>
                template<typename T> static bool IsClass()
                {
                    return IsClass( TypeInfo<T>().name() );
                }

                template<typename T> static const Metaclass& Get()
                {
                    if (!IsClass<T>())
                        Register(new Metaclass(Meta::Class<T>()));
                    return Get(TypeInfo<T>().name());
                }



                /** OPERATORS **/
                Metaclass& operator =(const Metaclass& other) = delete;
                ReflectionAPI Metaclass& operator =(Metaclass&& other) noexcept;

                bool operator ==(const Metaclass& other) const { return (this == &other); }
                bool operator !=(const Metaclass& other) const { return !(operator ==(other)); }

            private:
                
                /** DATA **/
                uint            _coreSize;
                Set<Field*>     _fields;
                uint            _id;
                bool            _isConstant;
                bool            _isReference;
                bool            _isPointer;
                string          _name;
                uint            _size;
                void*           _type;

                

                /** CONSTRUCTORS **/
                ReflectionAPI Metaclass();
                /// <summary> Constructs a new metaclass object containing information about a specific type. </summary>
                /// <param name="type"> The type for which the metaclass is to be constructed. </param>
                template<typename T> Metaclass(const Meta::Class<T>& type) : 
                    _coreSize       (Meta::Class<T>::CoreType::Size()),
                    _id             (TypeInfo<T>().hash_code()),
                    _isConstant     (Meta::Class<T>::IsConstant()),
                    _isReference    (Meta::Class<T>::IsReference()),
                    _isPointer      (Meta::Class<T>::IsPointer()),
                    _name           (TypeInfo<T>().name()),
                    _size           (Meta::Class<T>::Size()),
                    _type           (nullptr)
                {
                    
                }



                /** UTILITIES **/
                ReflectionAPI static void Register(Metaclass* type);

                template<typename T>
                static const std::type_info& TypeInfo() { return typeid(T); }

        };

    }
}
