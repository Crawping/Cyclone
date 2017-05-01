/* CHANGELOG
 * Written by Josh Grooms on 20170426
 */

#pragma once
#include "Interfaces/IReference.h"
#include "Runtime/Metaclass.h"



namespace Cyclone
{
    namespace Reflection
    {

        template<typename T>
        class Null : public IReference
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets whether the reference is constant qualified. </summary>
                bool IsConstant()                           const override { return _type.IsConstant(); }
                /// <summary> Gets whether the reference has a null value. </summary>
                bool IsNull()                               const override { return true; }
                /// <summary> Gets whether the reference is a native C++ reference to data. </summary>
                bool IsReference()                          const override { return _type.IsReference(); }
                /// <summary> Gets whether the reference is a native C++ pointer to data. </summary>
                bool IsPointer()                            const override { return _type.IsPointer(); }
                /// <summary> Gets the hash identifier of the native C++ type underlying the reference. </summary>
                uint TypeID()                               const override { return _type.ID(); }
                /// <summary> Gets the metaclass that describes the reference's underlying type. </summary>
                const Metaclass& Type()                     const override { return _type; }
                /// <summary> Gets the string name of the reference's underlying type. </summary>
                const string& TypeName()                    const override { return _type.Name(); }
                /// <summary> Gets the number of bytes required to store instances of the reference's underlying type. </summary>
                uint Size()                                 const override { return _type.Size(); }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new null-valued data reference. </summary>
                Null()                                      : _type(Meta::TypeOf<T>()) { }



                /** UTILITIES **/
                /// <summary> Creates a new null-valued data reference of the same underlying type. </summary>
                Null* Copy()                                const override { return new Null(); }



                /** OPERATORS **/
                /// <summary> Prevents casting the null reference to a native value type. </summary>
                /// <returns> This method always returns a <c>nullptr</c>. </returns>
                template<typename U> explicit operator U()  const { return nullptr; }

                /// <summary> Determines whether two separate data references are equivalent. </summary>
                /// <param name="other"> Another general data reference. </param>
                /// <returns> A Boolean <c>true</c> if the references are equivalent, or <c>false</c> otherwise. </returns>
                bool operator ==(const IReference& other)   const override { return Type() == other.Type(); }

            private:
                        
                const Metaclass& _type;

        };

        template<typename T> 
        class Reference : public Null<T>
        {
            public:

                /** PROPERTIES **/
                bool IsNull()                               const override { return false; }
                T& Value()                                  { return _value; }
                const T& Value()                            const { return _value; }
                


                /** CONSTRUCTOR **/
                Reference(T value)                          : _value(value) { }



                /** UTILITIES **/
                Reference* Copy()                           const override { return new Reference(_value); }



                /** OPERATORS **/
                explicit operator T()                       const { return _value; }

                bool operator ==(const IReference& other)   const override
                {
                    if (Type() != other.Type()) { return false; }

                    auto* y = dynamic_cast<const Reference<T>*>(&other);
                    return y ? (_value == y->_value) : false;
                }

            private:
                        
                T _value;
                        
        };

    }
}
