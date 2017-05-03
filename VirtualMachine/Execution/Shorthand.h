/* CHANGELOG
 * Written by Josh Grooms on 20170206
 */

#pragma once
#include "Execution/Instructions.h"



namespace Cyclone
{
    namespace Virtual
    {
        namespace Shorthand
        {
            enum Symbols : ubyte
            {
                nop,

                abort,
                all,

                call, callr,

                cat,

                copy,

                del,

                //defa, defm, defo, defp, defs, deft, defv,


                get,

                ind,

                jump, jumpi, jumpr, jumpri,

                load,

                pause,
                disp,
                rem,
                ret,

                set,
                swp,


                add,
                and,
                cast,
                cmp,
                dec,
                div,
                inc,
                mul,
                neg,
                not,
                or,
                sub,
                xor,
            };
        }
    }
}
