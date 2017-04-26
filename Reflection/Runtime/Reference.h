/* CHANGELOG
 * Written by Josh Grooms on 20170426
 */

#pragma once
#include "Interfaces/IReference.h"
#include "Meta/Class.h"



namespace Cyclone
{
    namespace Reflection
    {
        template<typename T> 
        class Reference : public IReference
        {
            public:

                /** PROPERTIES **/
                bool IsConstant()               const override { return Meta::Class<T>::IsConstant(); }
                bool IsReference()              const override { return Meta::Class<T>::IsReference(); }
                bool IsPointer()                const override { return Meta::Class<T>::IsPointer(); }
                uint TypeID()                   const override { return _info.hash_code(); }
                const std::type_info& Info()    const override { return _info; }
                const string& TypeName()        const override { return _info.name(); }
                uint Size()                     const override { return Meta::Class<T>::Size(); }



                /** CONSTRUCTOR **/
                Reference(T value) : 
                    _info(typeid(T)),
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
                        
                const std::type_info&   _info;
                T                       _value;
                        
        };
    }
}
