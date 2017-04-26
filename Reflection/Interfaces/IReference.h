/* CHANGELOG
 * Written by Josh Grooms on 20171425
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Reflection
    {
        using namespace Utilities;
        class Metaclass;



        /// <summary> An interface that represents a runtime reference to native data. </summary>
        class IReference
        {
            public:
                
                /** PROPERTIES **/
                /// <summary> Gets whether the reference is constant qualified. </summary>
                virtual bool IsConstant()               const = 0;
                /// <summary> Gets whether the reference is a native C++ reference to data. </summary>
                virtual bool IsReference()              const = 0;
                /// <summary> Gets whether the reference is a native C++ pointer to data. </summary>
                virtual bool IsPointer()                const = 0;
                /// <summary> Gets the class definition for the reference's underlying type. </summary>
                virtual const Metaclass& Type()         const = 0;
                /// <summary> Gets the hash identifier of the native C++ type used by the reference. </summary>
                virtual uint TypeID()                   const = 0;
                /// <summary> Gets the string name of the native C++ type used by the reference. </summary>
                virtual const string& TypeName()        const = 0;
                /// <summary> Gets the number of bytes required to stored instances of the native C++ type used by the reference. </summary>
                virtual uint Size()                     const = 0;



                /** DESTRUCTOR **/
                virtual ~IReference() { }



                /** UTILITIES **/
                virtual IReference* Copy()              const = 0;



                /** OPERATORS **/
                /// <summary> Determines whether this data reference is equivalent to another one. </summary>
                virtual bool operator ==(const IReference& other) const = 0;
                /// <summary> Determines whether this data reference is not equivalent to another one. </summary>
                virtual bool operator !=(const IReference& other) const { return !(operator ==(other)); }

        };
    }
}
