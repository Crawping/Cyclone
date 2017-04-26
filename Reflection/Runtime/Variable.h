/* CHANGELOG 
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "Meta/Utilities.h"
#include "Runtime/Reference.h"



namespace Cyclone
{
    namespace Reflection
    {
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
