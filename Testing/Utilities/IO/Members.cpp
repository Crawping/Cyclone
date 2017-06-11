/* CHANGELOG
 * Written by Josh Grooms on 20170609
 */

#include "IO/Property.h"
#include "Meta/Utilities.h"
#include "Spatial/Transform.h"
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

        TestStruct  _t0;
        Transform3D _t1;

        Property<TestStruct, float>                     _p1;
        Property<Transform3D, const Vector3&>           _p2;
        Property<Transform3D, float, const Vector3&>    _p3;



        _Members():
            _p1(&_t0, &TestStruct::Value, &TestStruct::Value),
            _p2(&_t1, &Transform3D::Position, &Transform3D::Position),
            _p3(&_t1, &Transform3D::Roll, &Transform3D::Orientation)
        {

        }
};



TEST_F(_Members, Construction)
{
    ASSERT_EQ(_t0.Value(),  0.0f);
    ASSERT_EQ(_p1(),        0.0f);
    ASSERT_EQ(_p1,          0.0f);
    ASSERT_EQ(_p2(),        Vector3::Zero);
    ASSERT_EQ(_p2,          Vector3::Zero); 
    ASSERT_EQ(_p3(),        0.0f);
    ASSERT_EQ(_p3,          0.0f);
}
TEST_F(_Members, Accessors)
{
    _p1(1.23456f);
    _p2(Vector3::One);
    _p3(Vector3::One);

    ASSERT_EQ(_p1,          1.23456f);
    ASSERT_EQ(_p2,          Vector3::One);
    ASSERT_EQ(_p3,          1.0f);

    _p1 = 3.14159f;
    _p2 = Vector3(2);
    _p3 = Vector3(3);

    ASSERT_EQ(_p1,          3.14159f);
    ASSERT_EQ(_p2,          Vector3(2));
    ASSERT_EQ(_p3,          3.0f);

    _p3 = _p2;
    ASSERT_EQ(_p3,          2.0f);
}
