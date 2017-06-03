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
        Volume _v5;


        _Volume():
            _v1(1, 2, 3, 10, 20, 30),
            _v2(Vector3::Zero, Vector3::One),
            _v3(Vector3(-1), Vector3(2)),
            _v4(Vector3(1), Vector3(-2)),
            _v5(Vector3(1), Vector3(2))
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
    constexpr Volume v1 = { 0, 0, 0, 1, 1, 1 };
    constexpr bool b1 = v1.Contains(v1);
    ASSERT_EQ(b1, true);

    ASSERT_EQ(_v0.Contains(_v1),    false);
    ASSERT_EQ(_v0.Contains(_v3),    false);
    ASSERT_EQ(_v0.Contains(_v4),    false);

    ASSERT_EQ(_v0.Contains(_v0),    true);
    ASSERT_EQ(_v3.Contains(_v0),    true);
    ASSERT_EQ(_v3.Contains(_v4),    true);
    ASSERT_EQ(_v4.Contains(_v0),    true);

    ASSERT_EQ(_v0.Contains(_v0, false),     false);
    ASSERT_EQ(_v3.Contains(_v4, false),     false);
}
TEST_F(_Volume, Equality)
{
    ASSERT_EQ(_v0, _v2);
    ASSERT_NE(_v0, _v1);
    ASSERT_EQ(_v3, _v3);
}
TEST_F(_Volume, Intersection)
{
    constexpr Volume v1 = Volume();
    constexpr Volume v2 = v1.Intersection(v1);
    ASSERT_EQ(v1, v2);

    ASSERT_EQ(_v0.Intersection(_v3),    _v0);
    ASSERT_EQ(_v0.Intersection(_v4),    _v0);
    ASSERT_EQ(_v0.Intersection(_v5),    Volume(Vector3(1), Vector3(0)));
}
TEST_F(_Volume, Intersects)
{
    constexpr Volume v1 = { 0, 0, 0, 1, 1, 1 };
    constexpr bool b1 = v1.Intersects(v1);
    ASSERT_EQ(b1, true);

    ASSERT_EQ(_v0.Intersects(_v2),  true);
    ASSERT_EQ(_v0.Intersects(_v5),  true);
    ASSERT_EQ(_v5.Intersects(_v0),  true);
    ASSERT_EQ(_v5.Intersects(_v1),  true);

    ASSERT_EQ(_v0.Intersects(_v1),  false);
    ASSERT_EQ(_v3.Intersects(_v1),  false);
    ASSERT_EQ(_v4.Intersects(_v1),  false);

    constexpr Volume v2 = { -10, 0, 0, 20, 0.01f, 0.01f };
    constexpr Volume v3 = { 0, -10, 0, 0.01f, 20, 0.01f };

    ASSERT_EQ(_v0.Intersects(v2),   true);
    ASSERT_EQ(_v0.Intersects(v3),   true);
    ASSERT_EQ(v2.Intersects(v3),    true);

    ASSERT_EQ(_v1.Intersects(v2),   false);
    ASSERT_EQ(_v1.Intersects(v3),   false);
}
TEST_F(_Volume, Rectify)
{
    constexpr Volume v1 = Volume( 10, 10, 10, -20, -20, -20 ).Rectify();
    constexpr Volume v2 = Volume( 3.14f, -5.78f, -10.13f, -7.75f, 8.91f, -1.23f ).Rectify();

    ASSERT_EQ(v1.Position(),    Vector3(-10));
    ASSERT_EQ(v1.Size(),        Vector3(20));
    ASSERT_EQ(v2.Position(),    Vector3(3.14f - 7.75f, -5.78f, -10.13f - 1.23f));
    ASSERT_EQ(v2.Size(),        Vector3(7.75f, 8.91f, 1.23f));
}
TEST_F(_Volume, Union)
{
    constexpr Volume v1 = Volume();
    constexpr Volume v2 = v1.Union(v1);
    ASSERT_EQ(v1, v2);

    ASSERT_EQ(_v0.Union(_v3),   _v3);
    ASSERT_EQ(_v0.Union(_v4),   _v3);
    ASSERT_EQ(_v0.Union(_v5),   Volume(Vector3(0), Vector3(3)));
}