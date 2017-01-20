/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Enumerator.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {

        struct Instructions : public Enumerator
        {
            enum Types
            {
                None        = 0,
                Add,
                Call,
                Compare,
                Divide,
                Get,
                Insert,
                Jump,
                Move,
                Multiply,
                Remove,
                Return,
                Set,
                Subtract,
                Swap,
            };

            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }
        };
    }
}
