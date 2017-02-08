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

                add, adda, addv,

                and, anda, andv,

                call, callm, callr,

                cast,

                cmp, cmpa, cmpv,

                cat,

                copy, copya, copyo, copyv,

                dec, deco, decv,

                del, dela, delo, dels, delv,

                defa, defm, defo, defp, defs, deft, defv,

                div, diva, divv,

                get, geta, geto, getv,

                inc, inca, incv,

                jump, jumpi, jumpr, jumpri,

                load, loada, loado,

                mul, mula, mulv,

                neg, nega, negv,

                not, nota, notv,

                or, ora, orv,

                pause,
                disp,
                rem,
                ret,

                set, seta, seto, setv,

                sub, suba, subv,

                swp, swpa, swpv,

                xor, xora, xorv,
            };
        }
    }
}
