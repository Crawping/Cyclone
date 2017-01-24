/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Enumerator.h"
#include "Collections/Vector.h"



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
                And,
                Call,
                Cast,
                Compare,
                Decrement,
                Delete,
                Divide,
                Get,
                Increment,
                Jump,
                JumpIf,
                Load,
                Multiply,
                Negate,
                Or,
                Remove,
                Return,
                Set,
                Store,
                Subtract,
                Swap,
                Xor,
            };

            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }
        };


        struct Instruction
        {
            Instructions        Command;
            Vector<uint, 3>     Operands;

            bool operator ==(const Instruction& other) const
            {
                return (Command == other.Command) && (Operands == other.Operands);
            }
            bool operator !=(const Instruction& other) const { return !(operator ==(other)); }
        };

    }
}
