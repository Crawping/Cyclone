/* CHANGELOG
 * Written by Josh Grooms on 20170122
 */


#include "VirtualMachine.h"
#include "Utilities.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::Utilities;



class _VirtualMachine : public testing::Test
{
    protected:

        Vector<int, 5>      _i1 = 0;
        Vector<string, 5>   _s1 = { "Variable0", "Variable1", "Variable2", "Variable3", "Variable4" };
        Vector<int, 5>      _v1 = { 0, 10, 20, 30, 40, 50 };

        VirtualClass        _c1;
        VirtualProperty     _p1;

        VirtualMachine      _m0;
        VirtualMachine      _m1;
        VirtualMemory       _t0;
        VirtualMemory       _t1;



        _VirtualMachine()
        {
            _m0.Data(&_t0);
            _m1.Data(&_t1);

            for (uint a = 0; a < _v1.Count(); a++)
            {
                _i1(a) = _t1.Insert(_s1(a));
                _t1.Set(_i1(a), _v1(a));
            }

            _c1 = VirtualClass(_i1(1));
            _p1 = VirtualProperty(_i1(2));
            _c1.Insert(_p1);

            _t1.Insert(_c1);
            _t1.Set(_c1.ID(), _p1.ID(), _i1(3), _v1(3));
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_VirtualMachine, DefaultConstruction)
{
    ASSERT_EQ(_m0.Data(), &_t0);
}



/** EXECUTION TESTS **/
TEST_F(_VirtualMachine, Addition)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::Add,                     0 },
        { Instructions::Store,              _i1(3) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) + _v1(2));
}
TEST_F(_VirtualMachine, Comparison)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::Compare,                 0 },
        { Instructions::Store,              _i1(3) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), compare(_v1(1), _v1(2)));
}
TEST_F(_VirtualMachine, Copying)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Copy,                    0 },
        { Instructions::MultiplyStore,      _i1(3) },
        { Instructions::CopyMemory,         { _i1(2), _i1(4), 0 } },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) * _v1(1));
    ASSERT_EQ(_t1.Get(_i1(4)), _v1(2));
}
TEST_F(_VirtualMachine, Decrementing)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Decrement,               0 },
        { Instructions::Decrement,               0 },
        { Instructions::Store,              _i1(3) },
        { Instructions::DecrementMemory,    _i1(2) },
        { Instructions::DecrementMemory,    _i1(2) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) - 2);
    ASSERT_EQ(_t1.Get(_i1(2)), _v1(2) - 2);
}
TEST_F(_VirtualMachine, Deletion)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Delete,             _i1(1) },
        { Instructions::Delete,             _i1(2) },
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::Compare,                 0 },
        { Instructions::Store,              _i1(3) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(1)), Literal());
    ASSERT_EQ(_t1.Get(_i1(2)), Literal());
    ASSERT_EQ(_t1.Get(_i1(3)), 0);
}
TEST_F(_VirtualMachine, Division)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::Divide,                  0 },
        { Instructions::Store,              _i1(3) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ((int)_t1.Get(_i1(3)).Value, _v1(1) / _v1(2));
}
TEST_F(_VirtualMachine, Incrementing)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Increment,               0 },
        { Instructions::Increment,               0 },
        { Instructions::Store,              _i1(3) },
        { Instructions::IncrementMemory,    _i1(2) },
        { Instructions::IncrementMemory,    _i1(2) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) + 2);
    ASSERT_EQ(_t1.Get(_i1(2)), _v1(2) + 2);
}
TEST_F(_VirtualMachine, Multiplication)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::MultiplyStore,      _i1(3) },
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::MultiplySet,        { _c1.ID(), _p1.ID(), _i1(3) } },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) * _v1(2));
    ASSERT_EQ(_t1.Get(_c1.ID(), _p1.ID(), _i1(3)), _v1(1) * _v1(2));
}
TEST_F(_VirtualMachine, ObjectInteraction)
{
    ASSERT_EQ(_t1.Get(_c1.ID(), _p1.ID(), _i1(3)), _v1(3));
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Get,                { _c1.ID(), _p1.ID(), _i1(3) } },
        { Instructions::Multiply,                0 },
        { Instructions::Set,                { _c1.ID(), _p1.ID(), _i1(3) } },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_c1.ID(), _p1.ID(), _i1(3)), _v1(1) * _v1(3));
}
TEST_F(_VirtualMachine, Subtraction)
{
    Vector<Instruction> cmds =
    {
        { Instructions::Load,               _i1(1) },
        { Instructions::Load,               _i1(2) },
        { Instructions::SubtractStore,      _i1(3) },
    };

    _m1.Execute(cmds);
    ASSERT_EQ(_t1.Get(_i1(3)), _v1(1) - _v1(2));
}