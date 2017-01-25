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
            enum Types : ubyte
            {
                None = 0,

                Add,
                AddSet,
                AddStore,

                And,
                AndSet,
                AndStore,

                Call,
                CallIf,
                CallRelative,
                CallRelativeIf,

                Cast,
                CastSet,
                CastStore,

                Compare,
                Decrement,

                Delete,

                Divide,
                DivideSet,
                DivideStore,

                Get,

                Increment,
                IncrementSet,
                IncrementStore,

                Jump,
                JumpIf,
                JumpRelative,
                JumpRelativeIf,

                Load,

                Multiply,
                MultiplySet,
                MultiplyStore,

                Negate,

                Or,
                OrSet,
                OrStore,

                Remove,
                Return,
                Set,
                Store,

                Subtract,
                SubtractSet,
                SubtractStore,

                Swap,

                Xor,
                XorSet,
                XorStore,
            };

            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }
            constexpr Instructions(ubyte type)          : Enumerator((int)type) { }
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
