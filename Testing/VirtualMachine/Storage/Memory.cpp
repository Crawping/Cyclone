/* CHANGELOG 
 * Written by Josh Grooms on 20170501
 */

#include "Virtual/Memory.h"
#include <gtest/gtest.h>

using namespace Cyclone::Virtual;



class _Memory:  public testing::Test 
{
    protected:


        Number      _n1;
        Reference   _rn1;
        Reference   _rn2;
        String      _s1;
        Reference   _rs1;
        Reference   _rs2;

        Memory      _m0;
        Memory      _m1;


        _Memory() :
            _n1(3.14159),
            _rn1(0, 0, ReferenceTypes::Number, hash("Testing")),
            _rn2(0, 0, ReferenceTypes::Reference, hash("NumberRef")),
            _s1("Testing"),
            _rs1(0, 0, ReferenceTypes::String, hash("Testing")),
            _rs2(0, 0, ReferenceTypes::Reference, hash("StringRef"))
        {
            _m1.Insert(_rn1, _n1);
            _m1.Insert(_rs1, _s1);
            _m1.Insert(_rn2, _rn1);
            _m1.Insert(_rs2, _rs1);
        }

};



/** CONSTRUCTOR **/
TEST_F(_Memory, Construction)
{
    ASSERT_EQ(_m0.ArrayCount(),         0);
    ASSERT_EQ(_m0.ClassCount(),         0);
    ASSERT_EQ(_m0.FunctionCount(),      0);
    ASSERT_EQ(_m0.NumberCount(),        0);
    ASSERT_EQ(_m0.ReferenceCount(),     0);
    ASSERT_EQ(_m0.StringCount(),        0);
}



/** UTILITIES **/
TEST_F(_Memory, Access)
{
    ASSERT_EQ(_m1.Access<String>(_rs1), _s1);
    ASSERT_EQ(_m1.Access<Number>(_rn1), _n1);

    ASSERT_EQ(_m1.Access<Reference>(_rn2),  _rn1);
    ASSERT_EQ(_m1.Access<Reference>(_rs2),  _rs1);
}
TEST_F(_Memory, Insertion)
{
    _m0.Insert(_rn1, _n1);
    _m0.Insert(_rs1, _s1);

    ASSERT_EQ(_m0.NumberCount(),        1);
    ASSERT_EQ(_m0.StringCount(),        1);

    ASSERT_EQ(_m1.NumberCount(),        1);
    ASSERT_EQ(_m1.StringCount(),        1);
    ASSERT_EQ(_m1.ReferenceCount(),     2);
}