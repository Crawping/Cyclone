/* CHANGELOG
 * Written by Josh Grooms on 20170626
 */

#include "Geometry/Mesh3D.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;



class _Mesh3D: public testing::Test 
{
    protected:

        Mesh3D _m0;
        Mesh3D _m1;
        Mesh3D _m2;

        _Mesh3D():
            _m1(Mesh3D::Cube(false)),
            _m2(Mesh3D::Cube(true))
        {

        }

};



TEST_F(_Mesh3D, Construction)
{
    ASSERT_EQ(_m0.Bounds(),     Volume::Empty);
    ASSERT_EQ(_m0.Count(),      0);
    ASSERT_EQ(_m0.IsEmpty(),    true);
    ASSERT_EQ(_m0.IsIndexed(),  false);
    ASSERT_EQ(_m0.Topology(),   PointTopologies::Triangles);
    ASSERT_EQ(_m0.Winding(),    WindingOrders::None);

    ASSERT_EQ(_m1.Bounds(),     Volume(Vector3(-0.5), Vector3(1)));
    ASSERT_EQ(_m1.Count(),      36);
    ASSERT_EQ(_m1.IsEmpty(),    false);
    ASSERT_EQ(_m1.IsIndexed(),  false);
    ASSERT_EQ(_m1.Topology(),   PointTopologies::Triangles);
    ASSERT_EQ(_m1.Winding(),    WindingOrders::None);

    ASSERT_EQ(_m2.Bounds(),     Volume(Vector3(-0.5), Vector3(1)));
    ASSERT_EQ(_m2.Count(),      36);
    ASSERT_EQ(_m2.IndexCount(), 36);
    ASSERT_EQ(_m2.PointCount(), 24);
    ASSERT_EQ(_m2.IsEmpty(),    false);
    ASSERT_EQ(_m2.IsIndexed(),  true);
    ASSERT_EQ(_m2.Topology(),   PointTopologies::Triangles);
    ASSERT_EQ(_m2.Winding(),    WindingOrders::None);
}