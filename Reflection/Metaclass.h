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



        /// <summary> A class that holds runtime-accessible information about other classes. </summary>
        class Metaclass
        {
            public:
                
                /** PROPERTIES **/    
                uint CoreSize()         const { return _coreSize; }
                /// <summary> Gets the unique numeric identifier associated with the class. </summary>
                uint ID()               const { return _id; }

                bool IsConstant()       const { return _isConstant; }
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
                    using Class = Meta::Class<T>;
                    const auto& type = TypeInfo<T>();
                    Class* c = new Class();

                    Metaclass m;
                    m._id           = type.hash_code();
                    m._coreSize     = Class::CoreType::Size();
                    m._isConstant   = Class::IsConstant();
                    m._isPointer    = Class::IsPointer();
                    m._isReference  = Meta::IsReference<T>();
                    m._name         = type.name();
                    m._size         = Class::Size();
                    m._type         = (void*)c;

                    m.TypeCheck     = new Method(&m, &Metaclass::IsOfType<T>);
                    
                    m.Register();
                    return m;
                }
                ReflectionAPI ~Metaclass();



                /** UTILITIES **/
                template<typename T> T Cast(T variable) const
                {
                    return IsOfType<T>() ? (T)variable : nullptr;
                }
                /// <summary> Determines whether the class contains a specific field. </summary>
                /// <returns> A Boolean <c>true</c> if the field is part of the class description, or <c>false</c> otherwise. </returns>
                /// <param name="field"> A field object to be tested for inclusion in the class description. </param>
                ReflectionAPI bool Contains(const Field& field) const;
                /// <summary> Adds a new field to the class description. </summary>
                /// <param name="type"> Another metaclass object that describes the type of the field being added. </param>
                /// <param name="name"> The human-readable string name of the field being added. </param>
                ReflectionAPI void Insert(const Metaclass& type, const string& name);



                /** STATIC UTILITIES **/
                /// <summary> Gets the metaclass object that corresponds with the string name of the underlying type. </summary>
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
                    const auto& type = TypeInfo<T>();
                    if (!IsClass(type.name()))
                        Create<T>();

                    return Get(type.name());
                }

            private:
                
                /** DATA **/
                uint        _coreSize;
                Set<Field*> _fields;
                uint        _id;
                bool        _isConstant;
                bool        _isReference;
                bool        _isPointer;
                string      _name;
                uint        _size;
                void*       _type;

                Method<bool, Metaclass>* TypeCheck;

                

                /** CONSTRUCTOR **/
                ReflectionAPI Metaclass();



                /** UTILITIES **/
                ReflectionAPI void Register() const;
                
                template<typename T>
                constexpr static const std::type_info& TypeInfo()   { return typeid(Meta::Dereference<T>::Type); }

                template<typename T>
                bool IsOfType() const 
                { 
                    using Class = Meta::Class<T>;

                    try                 { throw static_cast<Class*>(_type); }
                    catch (Class* type) { return true; }
                    catch (...)         { return false; }
                }

        };

    }
}
