/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Enumerator.h"
#include "Collections/Array.h"
#include "Storage/Reference.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Virtual
    {

        struct Instructions : public Enumerator
        {
            enum Types : ubyte
            {
                /// <summary> An empty instruction that performs no operations. </summary>
                None = 0,

                /// <summary> Terminates the process being executed. </summary>
                /// <remarks> This command takes no input arguments. </remarks>
                Abort,
                Allocate,
                /// <summary> </summary>
                Call,
                CallRelative,
                Concatenate,
                Copy,
                /// <summary> Deletes a variable from memory. </summary>
                Delete,

                //DefineArray,
                //DefineMethod,
                //DefineObject,
                //DefineProperty,
                //DefineStructure,
                //DefineType,
                //DefineVariable,

                /// <summary> Pushes an object property value onto the working variable stack. </summary>
                Get,
                Index,

                /// <summary> Sets the absolute position of the instruction pointer. </summary>
                Jump,
                JumpIf,
                /// <summary> Sets the position of the instruction pointer relative to its current value. </summary>
                JumpRelative,
                JumpRelativeIf,

                /// <summary> Pushes a value from memory onto the working variable stack. </summary>
                Load,
                /// <summary> Prevents any further execution of instructions until a resume command is received. </summary>
                Pause,
                /// <summary> Displays a string in the standard console output. </summary>
                Print,
                /// <summary> Discards the leading value on the working variable stack. </summary>
                Remove,
                /// <summary> Pops a stack frame and continues execution from the last function call position. </summary>
                Return,

                Set,
                /// <summary> Exchanges the positions of the two leading variables on the stack. </summary>
                Swap,



                Add,
                And,
                Cast,
                Compare,
                Decrement,
                Divide,
                Increment,
                Multiply,
                Negate,
                Not,
                Or,
                Subtract,
                Xor,
            };



            /** CONSTRUCTORS **/
            constexpr Instructions(ubyte type)          : Enumerator((int)type) { }
            constexpr Instructions(enum Types t = None) : Enumerator((int)t) { }

        };

       
        struct Instruction
        {
            

            Instructions            Command;
            Vector<Reference, 3>    Operands;


            /** CONSTRUCTORS **/
            Instruction() :
                Instruction(Instructions::None)
            {

            }
            Instruction(Instructions command, const Vector<Reference, 3>& operands) :
                Command(command),
                Operands(operands)
            {

            }
            Instruction(Instructions command, Reference x = 0, Reference y = 0, Reference z = 0) :
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
