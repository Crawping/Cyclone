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
                bool IsConstant()                           const override { return _type.IsConstant(); }
                bool IsNull()                               const override { return true; }
                bool IsReference()                          const override { return _type.IsReference(); }
                bool IsPointer()                            const override { return _type.IsPointer(); }
                uint TypeID()                               const override { return _type.ID(); }
                const Metaclass& Type()                     const override { return _type; }
                const string& TypeName()                    const override { return _type.Name(); }
                uint Size()                                 const override { return _type.Size(); }



                /** CONSTRUCTOR **/
                Null()                                      : _type(Meta::TypeOf<T>()) { }



                /** UTILITIES **/
                Null* Copy()                                const override { return new Null(); }



                /** OPERATORS **/
                template<typename U> explicit operator U()  const { return nullptr; }

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
