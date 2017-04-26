/* CHANGELOG
 * Written by Josh Grooms on 20170426
 */

#pragma once
#include "Interfaces/IClass.h"
#include "Meta/Class.h"



namespace Cyclone
{
    namespace Reflection
    {
        template<typename T> class Reference : public IClass
        {
            public:

                bool IsConstant()           const override { return Meta::Class<T>::IsConstant(); }
                bool IsReference()          const override { return Meta::Class<T>::IsReference(); }
                bool IsPointer()            const override { return Meta::Class<T>::IsPointer(); }
                uint TypeID()               const override { return 0; }
                const string& TypeName()    const override { return "Nothing"; }
                uint Size()                 const override { return Meta::Class<T>::Size(); }

                Reference(T value) : _value(value) { }

                template<typename U>
                explicit operator U() const { return nullptr; }
                explicit operator T() const { return _value; }


            private:
                        
                T _value;
                        
        };
    }
}
