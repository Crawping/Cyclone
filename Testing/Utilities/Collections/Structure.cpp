/* CHANGELOG
 * Written by Josh Grooms on 20170618
 */

#include "Collections/Structure.h"
#include "IO/Property.h"
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

        Structure
        <
            Array<int, 1, 3>, 
            Array<double, 4, 4>, 
            Array<ulong, 4, 5, 6>
        > _s3;

        _Structure():
            _s1(10, Transform3D()),
            _s2(10, Vector3::One, Constants::E<double>, Transform3D(1, 2, 3)),
            _s3({ 1, 2, 3 }, 8, 16)
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

    ASSERT_EQ(_s3.Count,        3);
    ASSERT_EQ(_s3.Offsets(1),   sizeof(Array<int, 1, 3>));
    ASSERT_EQ(_s3.Offsets(2),   sizeof(Array<int, 1, 3>) + sizeof(Array<double, 4, 4>));
    ASSERT_EQ(_s3.Size,         sizeof(_s3));
}


TEST_F(_Structure, Access)
{
    auto p10 = _s1.Property<0>();
    auto p11 = _s1.Property<1>();

    ASSERT_EQ(p10,              10);
    ASSERT_EQ(p11,              Transform3D());

    p10 = 20;
    p11 = Transform3D(1, 1, 1);

    ASSERT_EQ(p10,              20);
    ASSERT_EQ(p11,              Transform3D(1, 1, 1));

    ASSERT_EQ(_s1.Get<0>(),     20);
    ASSERT_EQ(_s1.Get<1>(),     Transform3D(1, 1, 1));
}
TEST_F(_Structure, Append)
{
    auto s1 = _s1.Append(Vector4(1.0f));

    ASSERT_EQ(s1.Count,         3);
    ASSERT_EQ(s1.Size,          _s1.Size + sizeof(Vector4));
    ASSERT_EQ(s1.Get<2>(),      Vector4(1.0f));

    Transform3D t1(10, 20, 30);

    auto p1 = Property<Transform3D, const Vector3&>(&t1, &Transform3D::Position, &Transform3D::Position);
    auto s2 = s1.Append(p1);

    ASSERT_EQ(s2.Count,                 s1.Count + 1);
    ASSERT_EQ(s2.Size,                  s1.Size + sizeof(p1));
    ASSERT_EQ(s2.Get<s1.Count>(),       Vector3(10));

    s2.Get<s1.Count>() = Vector3::One;
    ASSERT_EQ(s2.Get<s1.Count>(),       Vector3::One);
    ASSERT_EQ(t1.Position(),            Vector3::One);
}
TEST_F(_Structure, Get)
{
    ASSERT_EQ(_s1.Get<0>(),             10);
    ASSERT_EQ(_s1.Get<1>(),             Transform3D());

    ASSERT_EQ(_s2.Get<0>(),             10);
    ASSERT_EQ(_s2.Get<1>(),             Vector3::One);
    ASSERT_EQ(_s2.Get<2>(),             Constants::E<double>);
    ASSERT_EQ(_s2.Get<3>(),             Transform3D(1, 2, 3));

    ASSERT_EQ(_s3.Get<0>()(2U),         3);
    ASSERT_EQ(_s3.Get<1>()(3, 3),       8);
    ASSERT_EQ(_s3.Get<2>()(2, 2, 2),    16);

    ASSERT_EQ(_s2.Get<Vector3>(1),      Vector3::One);
    ASSERT_EQ(_s2.Get<double>(2),       Constants::E<double>);
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