/* CHANGELOG
 * Written by Josh Grooms on 20170601
 */

#include "Spatial/Volume.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Volume: public testing::Test
{
    protected:
        
        Volume _v0;
        Volume _v1;
        Volume _v2;
        Volume _v3;
        Volume _v4;


        _Volume():
            _v1(1, 2, 3, 10, 20, 30),
            _v2(Vector3::Zero, Vector3::One),
            _v3(Vector3(-1), Vector3(2)),
            _v4(Vector3(1), Vector3(-2))
        {

        }

};



TEST_F(_Volume, Construction)
{
    ASSERT_EQ(_v0.Position(),   Vector3::Zero);
    ASSERT_EQ(_v0.Size(),       Vector3::One);

    ASSERT_EQ(_v1.Position(),   Vector3(1, 2, 3));
    ASSERT_EQ(_v1.Size(),       Vector3(10, 20, 30));
}
TEST_F(_Volume, Contains)
{
    ASSERT_EQ(_v0.Contains(_v1),    false);
    ASSERT_EQ(_v0.Contains(_v3),    false);
    ASSERT_EQ(_v0.Contains(_v4),    false);

    ASSERT_EQ(_v0.Contains(_v0),    true);
    ASSERT_EQ(_v3.Contains(_v0),    true);
    ASSERT_EQ(_v3.Contains(_v4),    true);
    ASSERT_EQ(_v4.Contains(_v0),    true);
}
TEST_F(_Volume, Equality)
{
    ASSERT_EQ(_v0, _v2);
    ASSERT_NE(_v0, _v1);
    ASSERT_EQ(_v3, _v3);
}
TEST_F(_Volume, Rectification)
{
    constexpr Volume v1 = { 10, 10, 10, -20, -20, -20 };
    constexpr Volume v2 = v1.Rectify();
    constexpr Volume v3 = Volume( 3.14f, -5.78f, -10.13f, -7.75f, 8.91f, -1.23f ).Rectify();

    ASSERT_EQ(v2.Position(),    Vector3(-10));
    ASSERT_EQ(v2.Size(),        Vector3(20));
    ASSERT_EQ(v3.Position(),    Vector3(3.14f - 7.75f, -5.78f, -10.13f - 1.23f));
    ASSERT_EQ(v3.Size(),        Vector3(7.75f, 8.91f, 1.23f));
}