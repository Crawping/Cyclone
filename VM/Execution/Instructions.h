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
                CallRelative,

                Cast,
                CastStore,

                Compare,

                Copy,
                CopyMemory,

                Decrement,
                DecrementMemory,
                DecrementSet,
                DecrementStore,

                Delete,

                Divide,
                DivideSet,
                DivideStore,

                Get,

                Increment,
                IncrementMemory,
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
                NegateSet,
                NegateStore,

                Not,
                NotSet,
                NotStore,

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
                SwapMemory,

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
            Vector<int, 3>      Operands;

            bool operator ==(const Instruction& other) const
            {
                return (Command == other.Command) && (Operands == other.Operands);
            }
            bool operator !=(const Instruction& other) const { return !(operator ==(other)); }
        };

    }
}
