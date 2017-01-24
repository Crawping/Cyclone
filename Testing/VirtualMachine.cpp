/* CHANGELOG
 * Written by Josh Grooms on 20170122
 */


#include "VirtualMachine.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::Utilities;



class _VirtualMachine : public testing::Test
{
    protected:

        VirtualMachine  VM;
        VirtualTable    VT;

        _VirtualMachine() { VM.Data(&VT); }

};



TEST_F(_VirtualMachine, DefaultConstruction)
{
    ASSERT_EQ(VM.Data(), &VT);
}

TEST_F(_VirtualMachine, Execution)
{
    Vector<string, 3> varNames = { "variable1", "variable2", "variable3" };
    Vector<uint, 3> varIDs = 0;
    for (uint a = 0; a < 3; a++)
        varIDs(a) = VT.Insert(varNames(a));

    VT.Set(varIDs(0), 10);
    VT.Set(varIDs(1), 20);
    VT.Set(varIDs(2), 00);

    ASSERT_EQ(VT.Get(varIDs(0)), 10);
    ASSERT_EQ(VT.Get(varIDs(1)), 20);

    Vector<Instruction> cmds =
    {
        { Instructions::Load, varIDs(0) },
        { Instructions::Load, varIDs(1) },
        { Instructions::Add, { } },
        { Instructions::Store, varIDs(2) },
    };

    VM.Execute(cmds);

    ASSERT_EQ(VT.Get(varIDs(2)).Value, 30);
}