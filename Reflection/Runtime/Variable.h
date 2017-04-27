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
                /// <summary> Gets whether the variable has a null value. </summary>
                bool IsNull()                           const { return Data->IsNull(); }
                /// <summary> Gets whether the variable is a native C++ reference to data. </summary>
                bool IsReference()                      const { return Data->IsReference(); }
                /// <summary> Gets whether the variable is a native C++ pointer to data. </summary>
                bool IsPointer()                        const { return Data->IsPointer(); }
                /// <summary> Gets the metaclass that describes the variable's underlying type. </summary>
                const Metaclass& Type()                 const { return Data->Type(); }
                /// <summary> Gets the hash identifier of the native C++ type used by the reference. </summary>
                uint TypeID()                           const { return Data->TypeID(); }
                /// <summary> Gets the string name of the variable's underlying type. </summary>
                const string& TypeName()                const { return Data->TypeName(); }
                /// <summary> Gets the number of bytes required to store instances of the variable's type. </summary>
                uint Size()                             const { return Data->Size(); }



                /** CONSTRUCTORS & DESTRUCTOR **/
                /// <summary> Constructs a new null-valued variable. </summary>
                ReflectionAPI Variable();
                /// <summary> Constructs a new variable by transferring the contents of another variable. </summary>
                /// <param name="other"> Another runtime variable that is about to be moved. </param>
                ReflectionAPI Variable(Variable&& other);
                /// <summary> Constructs a new variable by copying the contents of another variable. </summary>
                /// <param name="other"> Another runtime variable that is to be copied. </param>
                ReflectionAPI Variable(const Variable& other);
                ReflectionAPI ~Variable();

                /// <summary> Constructs a new variable using the type and value of another native variable. </summary>
                /// <typeparam name="T"> The type of the inputted variable. </typeparam>
                /// <param name="value"> Any native C++ variable. </param>
                template<typename T> Variable(T value) : Data(new Reference<T>(value)) { }

                

                /** UTILITIES **/
                template<typename T>
                Reference<T>* Cast()                    const { return dynamic_cast<Reference<T>*>(Data); }



                /** OPERATORS **/
                ReflectionAPI Variable& operator =(Variable&& other);
                ReflectionAPI Variable& operator =(const Variable& other);

                ReflectionAPI bool operator ==(const Variable& other) const;
                ReflectionAPI bool operator !=(const Variable& other) const;

            protected:

                

            private:

                IReference* Data;
          
        };

    }
}
