/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#include "IO/Members.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Members: public testing::Test 
{
    protected:

        struct TestStruct
        {
            private:
                float _value = 0.0;

            public:
                float Value()                   const { return _value; }
                TestStruct& Value(float value)  { _value = value; return *this; }
        };

        TestStruct _t0;

        Property2<TestStruct, ConstMethodPointer<float, TestStruct>, MethodPointer<TestStruct&, TestStruct, float>> _p1;
        


        _Members():
            //_g1(&TestStruct::Value),
            //_s1(&TestStruct::Value),
            _p1(&_t0, &TestStruct::Value, &TestStruct::Value)
        {

        }
};



TEST_F(_Members, Construction)
{
    ASSERT_EQ(_t0.Value(),  0.0f);
    //ASSERT_EQ(_g1(_t0),     0.0f);
    ASSERT_EQ(_p1(),     0.0f);

    //_s1(_t0, 3.14159f);
    //ASSERT_EQ(_g1(_t0),     3.14159f);

    _p1(1.23456f);
    ASSERT_EQ(_p1(),     1.23456f);

    _p1 = 3.14159f;
    ASSERT_EQ(_p1,      3.14159f);
}
//TEST_F(_Members, )