/* CHANGELOG 
 * Written by Josh Grooms on 20170501
 */

#include "Collections/String.h"
#include "Execution/Shorthand.h"
#include "Primitives/Number.h"
#include "Virtual/Machine.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::VM::Virtual;
using namespace Cyclone::VM::Shorthand;



class _Machine : public testing::Test 
{
    protected:

        Machine     _m0;
        Machine     _m1;

        Number      _n1;
        Number      _n2;
        String      _s1;
        String      _s2;

        Reference   _rn1;
        Reference   _rn2;
        Reference   _rs1;
        Reference   _rs2;


        _Machine():
            _n1(3.14159),
            _n2(-2048),
            _s1("Testing"),
            _s2("This"),
            _rn1(0, 0, ReferenceTypes::Number, hash("Pi")),
            _rn2(0, 0, ReferenceTypes::Number, hash("Pow2")),
            _rs1(0, 0, ReferenceTypes::String, hash("TestString1")),
            _rs2(0, 0, ReferenceTypes::String, hash("TestString2"))
        {
            _m1.Insert(_rn1, _n1);
            _m1.Insert(_rn2, _n2);
            _m1.Insert(_rs1, _s1);
            _m1.Insert(_rs2, _s2);
        }

};



/** CONSTRUCTION **/
TEST_F(_Machine, Construction)
{
    const Memory& m(_m0.Memory());
    ASSERT_EQ(m.ArrayCount(),       0);
    ASSERT_EQ(m.ClassCount(),       0);
    ASSERT_EQ(m.FunctionCount(),    0);
    ASSERT_EQ(m.NumberCount(),      0);
    ASSERT_EQ(m.ReferenceCount(),   0);
    ASSERT_EQ(m.StringCount(),      0);
}



/** UTILITIES **/
TEST_F(_Machine, Insertion)
{
    const Memory& m(_m1.Memory());
    ASSERT_EQ(m.ArrayCount(),       0);
    ASSERT_EQ(m.ClassCount(),       0);
    ASSERT_EQ(m.FunctionCount(),    0);
    ASSERT_EQ(m.NumberCount(),      2);
    ASSERT_EQ(m.ReferenceCount(),   0);
    ASSERT_EQ(m.StringCount(),      2);
}



/** EXECUTION **/
TEST_F(_Machine, Aborting)
{
    Reference r1(0, 0, ReferenceTypes::Number, hash("Result"));

    Vector<Instruction> cmds = 
    {
        { add, r1, _rn1, _rn2 },
        { Instructions::Abort },
        { sub, r1, r1, _rn2 },
    };

    _m1.Execute(cmds);
    Number n1 = _m1.Memory().Access<Number>(r1);
    ASSERT_EQ(n1,                               _n1 + _n2);
}
TEST_F(_Machine, Computations)
{
    Memory& m(_m1.Memory());
    Reference r1(0, 0, ReferenceTypes::Number, hash("Result"));
    Vector<Instruction> cmds = { { add, r1, _rn1, _rn2 } };
    _m1.Execute(cmds);

    Number n1 = m.Access<Number>(r1);
    ASSERT_EQ(n1.Type(),                        NumericTypes::Float64);
    ASSERT_EQ(n1,                               _n1 + _n2);
    ASSERT_NE(n1,                               _n1 - _n2);

    cmds = { { sub, r1, _rn1, _rn2 } };
    _m1.Execute(cmds);

    Number n2 = m.Access<Number>(r1);
    ASSERT_EQ(n2.Type(),                        NumericTypes::Float64);
    ASSERT_EQ(n2,                               _n1 - _n2);
    ASSERT_NE(n2,                               n1);

    cmds = { { add, r1, r1, _rn2 } };
    _m1.Execute(cmds);

    Number n3 = m.Access<Number>(r1);
    ASSERT_EQ(n3.Type(),                        NumericTypes::Float64);
    ASSERT_FLOAT_EQ(n3.Value(),                 _n1.Value());
    ASSERT_NE(n3,                               n2);

    cmds = { { inc, r1 } };
    _m1.Execute(cmds);

    Number n4 = m.Access<Number>(r1);
    ASSERT_EQ(n4.Type(),                        NumericTypes::Float64);
    ASSERT_EQ(n4,                               n3 + Number(1));
    ASSERT_NE(n4,                               n2);

    cmds = { { cast, r1, _rn2 } };
    _m1.Execute(cmds);

    Number n5 = m.Access<Number>(r1);
    ASSERT_EQ(n5.Type(),                        NumericTypes::Integer32);
    ASSERT_EQ(n5,                               n4);
}
TEST_F(_Machine, Deletion)
{
    Memory& m(_m1.Memory());
    Number n1 = m.Access<Number>(_rn1);
    Number n2 = m.Access<Number>(_rn2);

    ASSERT_EQ(n1,                               _n1);
    ASSERT_NE(n1,                               Number(0));

    Vector<Instruction> cmds = { { del, _rn1 } };
    _m1.Execute(cmds);

    ASSERT_EQ(m.Access<Number>(_rn1),           Number(0));
    ASSERT_EQ(m.Access<Number>(_rn2),           n2);
}