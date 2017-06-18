/* CHANGELOG
 * Written by Josh Grooms on 20170618
 */

#include "Collections/Structure.h"
#include "Math/Constants.h"
#include "Spatial/Transform.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Structure: public testing::Test
{
    protected:

        Structure<int>                                  _s0;
        Structure<int, Transform3D>                     _s1;
        Structure<uint, Vector3, double, Transform3D>   _s2;


        _Structure():
            _s1(10, Transform3D()),
            _s2(10, Vector3::One, Constants::E<double>, Transform3D(1, 2, 3))
        {

        }

};



TEST_F(_Structure, Construction)
{
    ASSERT_EQ(_s0.Count,        1);
    ASSERT_EQ(_s0.Offsets(0),   0);
    ASSERT_EQ(_s0.Offsets(1),   sizeof(int));
    ASSERT_EQ(_s0.Size,         sizeof(int));
    ASSERT_EQ(_s0.Size,         sizeof(_s0));

    ASSERT_EQ(_s1.Count,        2);
    ASSERT_EQ(_s1.Offsets(0),   0);
    ASSERT_EQ(_s1.Offsets(1),   sizeof(int));
    ASSERT_EQ(_s1.Offsets(2),   sizeof(int) + sizeof(Transform3D));
    ASSERT_EQ(_s1.Size,         sizeof(int) + sizeof(Transform3D));
    ASSERT_EQ(_s1.Size,         sizeof(_s1));

    ASSERT_EQ(_s2.Count,        4);
    ASSERT_EQ(_s2.Offsets(0),   0);
    ASSERT_EQ(_s2.Offsets(1),   sizeof(uint));
    ASSERT_EQ(_s2.Offsets(2),   sizeof(uint) + sizeof(Vector3));
    ASSERT_EQ(_s2.Offsets(3),   sizeof(uint) + sizeof(Vector3) + sizeof(double));
    ASSERT_EQ(_s2.Offsets(4),   sizeof(uint) + sizeof(Vector3) + sizeof(double) + sizeof(Transform3D));
    ASSERT_EQ(_s2.Size,         sizeof(uint) + sizeof(Vector3) + sizeof(double) + sizeof(Transform3D));
    ASSERT_EQ(_s2.Size,         sizeof(_s2));
}

TEST_F(_Structure, Get)
{
    ASSERT_EQ(_s1.Get<0>(),     10);
    ASSERT_EQ(_s1.Get<1>(),     Transform3D());

    ASSERT_EQ(_s2.Get<0>(),     10);
    ASSERT_EQ(_s2.Get<1>(),     Vector3::One);
    ASSERT_EQ(_s2.Get<2>(),     Constants::E<double>);
    ASSERT_EQ(_s2.Get<3>(),     Transform3D(1, 2, 3));
}
TEST_F(_Structure, Set)
{
    _s1
        .Set<0>(20)
        .Set<1>(Transform3D(Vector3::One));

    ASSERT_EQ(_s1.Get<0>(),     20);
    ASSERT_EQ(_s1.Get<1>(),     Transform3D(Vector3::One));

    _s2
        .Set<0>(100)
        .Set<1>(Vector3(5.0f))
        .Set<2>(Constants::Pi<double>)
        .Set<3>(Transform3D(10, 20, 30));

    ASSERT_EQ(_s2.Get<0>(),     100);
    ASSERT_EQ(_s2.Get<1>(),     Vector3(5.0f));
    ASSERT_EQ(_s2.Get<2>(),     Constants::Pi<double>);
    ASSERT_EQ(_s2.Get<3>(),     Transform3D(10, 20, 30));

}