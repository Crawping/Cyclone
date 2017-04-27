/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "Enumerator.h"
#include "Runtime/Variable.h"



namespace Cyclone
{
    namespace VM
    {
        using namespace Utilities;

        namespace Virtual
        {

            struct PrimitiveTypes : public Enumerator
            {
                enum Types : ubyte
                {
                    Null        = 0,
                    Array       = 1,
                    Boolean     = 2,
                    Double      = 3,
                    Float       = 4,
                    Function    = 5,
                    Integer     = 6,
                    Object      = 7,
                    Reference   = 8,
                    String      = 9,
                };
            };


            struct VariableType
            {
                PrimitiveTypes  Primary;
                PrimitiveTypes  Secondary;
                
            };


            struct Variable
            {




            };



        }
    }
}
