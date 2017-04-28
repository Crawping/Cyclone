/* CHANGELOG
 * Written by Josh Grooms on 20170427
 */

#pragma once
#include "TypeDefinitions.h"
#include "Collections/Vector.h"




namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {
            using namespace Utilities;



            /* REGISTERS 
             *  - Input     (I)
             *  - Local     (L)
             *  - Output    (O)
             *  - Temporary (T)
             */

            /* MEMORY 
             *  - Global
             *  - Namespace
             *      > Arrays
             *      > Objects
             *          >> Arrays
             *          >> Objects
             *          >> Functions
             *          >> Variables
             *      > Functions
             *      > Variables
             */




            /* REGISTER ADDRESSING
             *  - 64-bit unsigned integer
             *      > Base              (16)
             *      > Offset            (16)
             *      > Count             (16)
             *      > Stride            (16)
             */

            /* MEMORY ADDRESSING
             *  - 64-bit unsigned integer
             *      > Base              (32)
             *      > Offset            (32)
             */



            // add      RX RY RZ    (Register-X = Register-Y + Register-Z)
            // add      @X @Y @Z

            // call     RX RY RZ    (Register-X(2:4:3) = Register-Y(Register-Z))

            // call     @X

            // load     

            // move     RX RY RZ    
            // move     @X RX
            // move     RX @X



            struct Instruction
            {
                ubyte               Command;
                Vector<double, 3>   Operands;


                /** CONSTRUCTORS **/
                Instruction() :
                    Instruction(0)
                {

                }
                Instruction(ubyte command, const Vector<double, 3>& operands) :
                    Command(command),
                    Operands(operands)
                {

                }
                Instruction(ubyte command, double x = 0, double y = 0, double z = 0) :
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
}
