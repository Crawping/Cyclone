/* CHANGELOG
 * Written by Josh Grooms on 20170122
 */


#include "VirtualMachine.h"
#include "Utilities.h"
#include "Execution/Shorthand.h"
#include <gtest/gtest.h>

using namespace Cyclone::Virtual;
using namespace Cyclone::Utilities;
using namespace Cyclone::Virtual::Shorthand;

namespace S = Cyclone::Virtual::Shorthand;


//class _VirtualMachine : public testing::Test
//{
//    protected:
//
//        Vector<int, 5>      _i1 = 0;
//        Vector<int, 5>      _i2 = 0;
//        Vector<string, 5>   _s1 = { "Variable0", "Variable1", "Variable2", "Variable3", "Variable4" };
//        Vector<string, 5>   _s2 = { "Class0", "Class1", "Class2", "Class3", "Class4" };
//        Vector<int, 5>      _v1 = { 0, 10, 20, 30, 40, 50 };
//
//        VirtualClass        _c1;
//        VirtualProperty     _p1;
//
//        VirtualMachine      _m0;
//        VirtualMachine      _m1;
//        VirtualMemory       _t0;
//        VirtualMemory       _t1;
//
//
//
//        _VirtualMachine()
//        {
//            _m0.Data(&_t0);
//            _m1.Data(&_t1);
//
//            for (uint a = 0; a < _v1.Count(); a++)
//            {
//                _i1(a) = _t1.Insert(_s1(a));
//                _i2(a) = _t1.Insert(_s2(a));
//                _t1.SetVariable(_i1(a), _v1(a));
//            }
//
//            _c1 = VirtualClass(_i2(0));
//            _p1 = VirtualProperty(_i1(0), { VariableTypes::Integer });
//            _c1.Insert(_p1);
//
//            _t1.Insert(_c1);
//            _t1.SetObject(_c1.ID(), _p1.ID(), _i1(0), _v1(3));
//            _t1.SetObject(_c1.ID(), _p1.ID(), _i1(1), _v1(4));
//        }
//
//};
//
//
//
///** CONSTRUCTION TESTS **/
//TEST_F(_VirtualMachine, DefaultConstruction)
//{
//    ASSERT_EQ(_m0.Data(), &_t0);
//}
//
//
//
///** EXECUTION TESTS **/
//TEST_F(_VirtualMachine, Addition)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,    _i1(1) },
//        { getv,    _i1(2) },
//        { add,          0 },
//        { setv,    _i1(3) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) + _v1(2));
//}
//TEST_F(_VirtualMachine, Comparison)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { getv,     _i1(2) },
//        { cmp,           0 },
//        { setv,     _i1(3) },
//        { cmpv,     _i1(4), _i1(1), _i1(2) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), compare(_v1(1), _v1(2)));
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _t1.GetVariable(_i1(4)));
//}
//TEST_F(_VirtualMachine, Copying)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { copy,          0 },
//        { mul,           0 },
//        { setv,     _i1(3) },
//        { copyv,    _i1(2), _i1(4) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) * _v1(1));
//    ASSERT_EQ(_t1.GetVariable(_i1(4)), _v1(2));
//}
//TEST_F(_VirtualMachine, Decrementing)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { dec,           0 },
//        { dec,           0 },
//        { setv,     _i1(3) },
//        { deco,     _c1.ID(), _p1.ID() },
//        { decv,     _i1(2) },
//        { decv,     _i1(2) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) - 2);
//    ASSERT_EQ(_t1.GetVariable(_i1(2)), _v1(2) - 2);
//}
//TEST_F(_VirtualMachine, Deletion)
//{
//    Vector<Instruction> cmds =
//    {
//        { delv,     _i1(1) },
//        { delv,     _i1(2) },
//        { getv,     _i1(1) },
//        { getv,     _i1(2) },
//        { cmp,           0 },
//        { setv,     _i1(3) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(1)), VirtualVariable());
//    ASSERT_EQ(_t1.GetVariable(_i1(2)), VirtualVariable());
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), 0);
//}
//TEST_F(_VirtualMachine, Division)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { getv,     _i1(2) },
//        { S::div,        0 },
//        { setv,     _i1(3) },
//        { divv,     _i1(4), _i1(1), _i1(2) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ((int)_t1.GetVariable(_i1(3)).Value(), _v1(1) / _v1(2));
//    ASSERT_EQ((int)_t1.GetVariable(_i1(4)).Value(), _v1(1) / _v1(2));
//}
//TEST_F(_VirtualMachine, Incrementing)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { inc,           0 },
//        { inc,           0 },
//        { setv,     _i1(3) },
//        { incv,     _i1(2) },
//        { incv,     _i1(2) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) + 2);
//    ASSERT_EQ(_t1.GetVariable(_i1(2)), _v1(2) + 2);
//}
//TEST_F(_VirtualMachine, Jumping)
//{
//    int sid = _t1.Insert("Success!");
//    int fid = _t1.Insert("Failure!");
//
//    Vector<Instruction> cmds =
//    {
//        { getv,      _i1(1) },
//        { getv,      _i1(2) },
//        { mul,            0 },
//
//        { getv,      _i1(1) },
//        { jumpri,   0, 2, 2 },
//        { disp,         sid },
//        { jumpr,          1 },
//        { disp,         fid },
//
//        { getv,      _i1(2) },
//        { S::div,         0 },
//
//        { getv,      _i1(1) },
//        { jumpri,   0, 0, 2 },
//        { disp,         fid },
//        { jumpr,          1 },
//        { disp,         sid },
//    };
//
//    _m1.Execute(cmds);
//}
//TEST_F(_VirtualMachine, Multiplication)
//{
//    Vector<Instruction> cmds =
//    {
//        { mulv,      _i1(3), _i1(1), _i1(2) },
//        { getv,      _i1(1) },
//        { getv,      _i1(2) },
//        { mul,            0 },
//        { seto,      _c1.ID(), _p1.ID(), _i1(3) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) * _v1(2));
//    ASSERT_EQ(_t1.GetObject(_c1.ID(), _p1.ID(), _i1(3)), _v1(1) * _v1(2));
//}
//TEST_F(_VirtualMachine, ObjectInteraction)
//{
//    ASSERT_EQ(_t1.GetObject(_c1.ID(), _p1.ID(), _i1(0)), _v1(3));
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { geto,     _c1.ID(), _p1.ID(), _i1(0) },
//        { mul,           0 },
//        { copy,          0 },
//        { seto,     _c1.ID(), _p1.ID(), _i1(0) },
//        { inc,           0 },
//        { seto,     _c1.ID(), _p1.ID(), _i1(1) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetObject(_c1.ID(), _p1.ID(), _i1(0)), _v1(1) * _v1(3));
//    ASSERT_EQ(_t1.GetObject(_c1.ID(), _p1.ID(), _i1(1)), _v1(1) * _v1(3) + 1);
//}
//TEST_F(_VirtualMachine, Subtraction)
//{
//    Vector<Instruction> cmds =
//    {
//        { getv,     _i1(1) },
//        { getv,     _i1(2) },
//        { sub,           0 },
//        { setv,     _i1(3) },
//        { subv,     _i1(4), _i1(1), _i1(2) },
//    };
//
//    _m1.Execute(cmds);
//    ASSERT_EQ(_t1.GetVariable(_i1(3)), _v1(1) - _v1(2));
//    ASSERT_EQ(_t1.GetVariable(_i1(4)), _v1(1) - _v1(2));
//}