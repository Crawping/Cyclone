/* CHANGELOG 
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "Interfaces/IClass.h"
#include "Meta/Class.h"
#include "Meta/Primitives.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;


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



        class Variable
        {
            public:
                
                /** PROPERTIES **/
                bool IsConstant()           const { return Data->IsConstant(); }
                bool IsReference()          const { return Data->IsReference(); }
                bool IsPointer()            const { return Data->IsPointer(); }
                uint TypeID()               const { return Data->TypeID(); }
                const string& TypeName()    const { return Data->TypeName(); }
                uint Size()                 const { return Data->Size(); }



                /** CONSTRUCTORS & DESTRUCTOR **/
                Variable()                              : Data(new Reference<int>(0)) { }
                template<typename T> Variable(T value)  : Data(new Reference<T>(value)) { }
                ~Variable()                             { delete Data; }



                /** UTILITIES **/
                template<typename T>
                Reference<T>* Cast()        const { return dynamic_cast<Reference<T>*>(Data); }

               

            private:

                IClass* Data;
          
        };
    }
}
