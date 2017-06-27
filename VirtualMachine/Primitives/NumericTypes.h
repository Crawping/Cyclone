/* CHANGELOG
 * Written by Josh Grooms on 20170429
 */

#pragma once
#include "Enumerator.h"
#include "TypeDefinitions.h"
#include "VMAPI.h"
#include "Meta/Utilities.h"



namespace Cyclone
{
    namespace Virtual
    {
        using namespace Utilities;

        struct NumericTypes : public Enumerator
        {
            enum Types
            {
                Null = 0,

                Character,

                Float32,

                Float64,

                Integer8,

                Integer8U,

                Integer16,

                Integer16U,

                Integer32,

                Integer32U,

                Integer64,

                Integer64U,

                Reference,
            };



            /** PROPERTIES **/
            VMAPI constexpr bool IsIntegral()       const;
            VMAPI constexpr bool IsSigned()         const;
            VMAPI constexpr uint Size()             const;



            /** CONSTRUCTORS **/
            constexpr NumericTypes(uint type):                  Enumerator((int)type) { }
            constexpr NumericTypes(enum Types t = Integer32):   Enumerator((int)t) { }



            /** UTILITIES **/
            VMAPI string ToString()                 const;
            VMAPI constexpr static NumericTypes Max(NumericTypes x, NumericTypes y);

            
            template<typename T>
            constexpr static NumericTypes TypeOf(T value)
            {
                //using namespace Cyclone::Reflection;
                return 
                    Meta::TypeEquals<char>(value)   ? Character     :
                    Meta::TypeEquals<float>(value)  ? Float32       :
                    Meta::TypeEquals<double>(value) ? Float64       :
                    Meta::TypeEquals<byte>(value)   ? Integer8      :
                    Meta::TypeEquals<ubyte>(value)  ? Integer8U     :
                    Meta::TypeEquals<int>(value)    ? Integer32     : 
                    Meta::TypeEquals<uint>(value)   ? Integer32U    :
                    Meta::TypeEquals<long>(value)   ? Integer64     :
                    Meta::TypeEquals<ulong>(value)  ? Integer64U    : Null;
            }

        };



    }
}
