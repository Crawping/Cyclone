/* CHANGELOG
 * Written by Josh Grooms on 20170206
 */

#pragma once
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Shorthand
        {
            enum Symbols : ubyte
            {
                nop,

                abort,

                add,

                and,

                call, callr,

                cast,

                cmp, 

                cat,

                copy,

                dec,

                del,

                //defa, defm, defo, defp, defs, deft, defv,

                div,

                get,

                inc,

                ind,

                jump, jumpi, jumpr, jumpri,

                load,

                mul,

                neg,

                not,

                or,

                pause,
                disp,
                rem,
                ret,

                set,

                sub,

                swp,

                xor,
            };
        }
    }
}
