#include "Utilities.h"
#include "Primitives/NumericTypes.h"
#include "Meta/Class.h"
#include "Meta/Utilities.h"

using namespace Cyclone::Reflection;



namespace Cyclone
{
    namespace Virtual
    {

        /** PROPERTIES **/
        constexpr bool NumericTypes::IsIntegral() const
        {
            return
                Value != Null       &&
                Value != Float32    &&
                Value != Float64;
        }
        constexpr bool NumericTypes::IsSigned() const
        {
            return 
                Value != Null       &&
                Value != Integer8U  && 
                Value != Integer16U && 
                Value != Integer32U && 
                Value != Integer64U &&
                Value != Reference;
        }
        constexpr uint NumericTypes::Size() const
        {
            return
                (Value == Null)                                                 ? 0 :
                (Value == Character || Value == Integer8 || Value == Integer8U) ? 1 :
                (Value == Integer16 || Value == Integer16U)                     ? 2 :
                (Value == Float32 || Value == Integer32 || Value == Integer32U) ? 4 : 8;
        }



        /** UTILITIES **/
        constexpr NumericTypes NumericTypes::Max(NumericTypes x, NumericTypes y)
        {
            return
                (x == Null || y == Null)        ? Null      : 
                (x == Float64 || y == Float64)  ? Float64   : 
                (x == Float32 || y == Float32)  ? Float32   :
                (x > y)                         ? x         : y;
        }

    }
}