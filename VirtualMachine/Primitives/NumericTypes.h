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
    namespace VM
    {
        using namespace Utilities;

        struct NumericTypes : public Enumerator
        {
            enum Types
            {
                Null        = 0,

                Character   = 1,

                Float32     = 2,

                Float64     = 3,

                /// <summary> A binary logical variable that can only take on values of either true or false. </summary>
                Integer8    = 4,

                Integer8U   = 5,

                Integer16   = 6,

                Integer16U  = 7,

                Integer32   = 8,

                Integer32U  = 9,

                Integer64   = 10,

                Integer64U  = 11,
            };


            /** PROPERTIES **/
            VMAPI constexpr bool IsIntegral()       const;
            VMAPI constexpr bool IsSigned()         const;
            VMAPI constexpr uint Size()             const;




            /** CONSTRUCTORS **/
            constexpr NumericTypes(uint type)                   : Enumerator((int)type) { }
            constexpr NumericTypes(enum Types t = Integer32)    : Enumerator((int)t) { }



            /** UTILITIES **/
            VMAPI string ToString()                 const;

            VMAPI constexpr static NumericTypes Max(NumericTypes x, NumericTypes y);

            
            template<typename T>
            constexpr static NumericTypes TypeOf(T value)
            {
                using P = NumericTypes;
                using namespace Cyclone::Reflection;

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
