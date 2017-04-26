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
        class Reference : public IReference
        {
            public:

                /** PROPERTIES **/
                bool IsConstant()               const override { return _type.IsConstant(); }
                bool IsReference()              const override { return _type.IsReference(); }
                bool IsPointer()                const override { return _type.IsPointer(); }
                uint TypeID()                   const override { return _type.ID(); }
                const Metaclass& Type()         const override { return _type; }
                const string& TypeName()        const override { return _type.Name(); }
                uint Size()                     const override { return _type.Size(); }



                /** CONSTRUCTOR **/
                Reference(T value) : 
                    _type(Meta::TypeOf(value)),
                    _value(value)
                { 

                }



                /** UTILITIES **/
                Reference* Copy()           const override { return new Reference(_value); }



                /** OPERATORS **/
                template<typename U>
                explicit operator U()       const { return nullptr; }
                explicit operator T()       const { return _value; }



                bool operator ==(const IReference& other) const
                {
                    auto* y = dynamic_cast<const Reference<T>*>(&other);
                    return y ? (_value == y->_value) : false;
                }

            private:
                        
                const Metaclass&    _type;
                T                   _value;
                        
        };
    }
}
