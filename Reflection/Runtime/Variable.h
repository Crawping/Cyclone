/* CHANGELOG 
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "ReflectionAPI.h"
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
                /// <summary> Gets whether the variable is constant qualified. </summary>
                bool IsConstant()                       const { return Data->IsConstant(); }
                /// <summary> Gets whether the variable is a native C++ reference to data. </summary>
                bool IsReference()                      const { return Data->IsReference(); }
                /// <summary> Gets whether the variable is a native C++ pointer to data. </summary>
                bool IsPointer()                        const { return Data->IsPointer(); }

                const Metaclass& Type()                 const { return Data->Type(); }
                /// <summary> Gets the hash identifier of the native C++ type used by the reference. </summary>
                uint TypeID()                           const { return Data->TypeID(); }
                /// <summary> Gets the string name of the variable's underlying type. </summary>
                const string& TypeName()                const { return Data->TypeName(); }
                /// <summary> Gets the number of bytes required to store instances of the variable's type. </summary>
                uint Size()                             const { return Data->Size(); }



                /** CONSTRUCTORS & DESTRUCTOR **/
                ReflectionAPI Variable();
                ReflectionAPI Variable(Variable&& other);
                ReflectionAPI Variable(const Variable& other);
                ReflectionAPI ~Variable();

                template<typename T> Variable(T value) : Data(new Reference<T>(value)) { }



                /** UTILITIES **/
                template<typename T>
                Reference<T>* Cast()                    const { return dynamic_cast<Reference<T>*>(Data); }



                /** OPERATORS **/
                ReflectionAPI Variable& operator =(Variable&& other);
                ReflectionAPI Variable& operator =(const Variable& other);

                ReflectionAPI bool operator ==(const Variable& other) const;
                ReflectionAPI bool operator !=(const Variable& other) const;

            private:

                IReference* Data;
          
        };
    }
}
