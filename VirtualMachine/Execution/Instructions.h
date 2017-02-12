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
                /// <summary> An empty instruction that performs no operations. </summary>
                None = 0,

                /// <summary> Terminates the process being executed. </summary>
                Abort,

                Add,
                AddArrays,
                AddVariables,

                And,
                AndArrays,
                AndVariables,

                Call,
                CallFunction,
                CallMethod,
                CallRelative,

                Cast,

                Compare,
                CompareArrays,
                CompareVariables,

                Concatenate,

                Copy,
                CopyArray,
                CopyObject,
                CopyVariable,

                Decrement,
                DecrementObject,
                DecrementVariable,

                /// <summary> Deletes a variable from memory. </summary>
                Delete,
                DeleteArray,
                DeleteObject,
                DeleteStructure,
                DeleteVariable,

                DefineArray,
                DefineMethod,
                DefineObject,
                DefineProperty,
                DefineStructure,
                DefineType,
                DefineVariable,

                Divide,
                DivideArrays,
                DivideVariables,

                /// <summary> Pushes an object property value onto the working variable stack. </summary>
                Get,
                GetArray,
                GetObject,
                GetVariable,

                Increment,
                IncrementObject,
                IncrementVariable,

                /// <summary> Sets the absolute position of the instruction pointer. </summary>
                Jump,
                JumpIf,
                /// <summary> Sets the position of the instruction pointer relative to its current value. </summary>
                JumpRelative,
                JumpRelativeIf,

                /// <summary> Pushes a value from memory onto the working variable stack. </summary>
                Load,
                LoadArray,
                LoadObject,

                Multiply,
                MultiplyArrays,
                MultiplyVariables,

                Negate,
                NegateArray,
                NegateVariable,

                Not,
                NotArray,
                NotVariable,

                Or,
                OrArrays,
                OrVariables,

                /// <summary> Prevents any further execution of instructions until a resume command is received. </summary>
                Pause,
                /// <summary> Displays a string in the standard console output. </summary>
                Print,
                /// <summary> Discards the leading value on the working variable stack. </summary>
                Remove,
                /// <summary> Pops a stack frame and continues execution from the last function call position. </summary>
                Return,

                Set,
                SetArray,
                SetObject,
                SetVariable,

                Subtract,
                SubtractArrays,
                SubtractVariables,

                /// <summary> Exchanges the positions of the two leading variables on the stack. </summary>
                Swap,
                SwapArray,
                /// <summary> Exchanges the variables found at two memory locations. </summary>
                SwapVariables,

                Xor,
                XorArrays,
                XorVariables,
            };



            /** CONSTRUCTORS **/
            constexpr Instructions(ubyte type)          : Enumerator((int)type) { }
            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }

        };


        struct Instruction
        {
            Instructions        Command;
            Vector<int, 3>      Operands;


            /** CONSTRUCTORS **/
            Instruction() :
                Instruction(Instructions::None)
            {

            }
            Instruction(Instructions command, const Vector<int, 3>& operands) :
                Command(command),
                Operands(operands)
            {

            }
            Instruction(Instructions command, int x = 0, int y = 0, int z = 0) :
                Command(command),
                Operands({ x, y, z })
            {

            }


            bool operator ==(const Instruction& other) const
            {
                return (Command == other.Command) && (Operands == other.Operands);
            }
            bool operator !=(const Instruction& other) const { return !(operator ==(other)); }
        };

    }
}
