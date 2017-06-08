/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#include "Geometry/Mesh3D.h"
#include "Libraries/Material3D.h"
#include "Resources/Resource.h"
#include "Resources/ResourceLibrary2.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;



class _Resource: public testing::Test
{
    protected:

        ResourceLibrary2        _l0;

        Resource<Mesh3D>        _g0;
        Resource<Mesh3D>        _g1;
        Resource<Mesh3D>        _g2;
        Resource<Mesh3D>        _g3;
        
        Resource<Material3D>    _m0;
        Resource<Material3D>    _m1;

        _Resource():
            _g1(_l0.Create<Mesh3D>("G1")),
            _g2(_l0.Create<Mesh3D>("G2", Constructor<Mesh3D>())),
            _g3(_l0.Create<Mesh3D>("G3", Function<Mesh3D, bool>(&Mesh3D::Cube), true)),
            _m1(_l0.Create<Material3D>("M1"))
        {
            
        }

};



TEST_F(_Resource, Construction)
{
    ASSERT_EQ(_g1.Name(),                   "G1");
    ASSERT_EQ(_g1->IsEmpty(),               true);
    ASSERT_EQ(_g1->IsIndexed(),             false);
    ASSERT_EQ(_g1->Count(),                 0);

    ASSERT_EQ(_g2.Name(),                   "G2");
    ASSERT_EQ(_g2->IsEmpty(),               true);
    ASSERT_EQ(_g2->IsIndexed(),             false);
    ASSERT_EQ(_g2->Count(),                 0);

    ASSERT_EQ(_g3.Name(),                   "G3");
    ASSERT_EQ(_g3->IsEmpty(),               false);
    ASSERT_EQ(_g3->IsIndexed(),             true);
    ASSERT_EQ(_g3->Count(),                 36);
}
TEST_F(_Resource, Get)
{
    ASSERT_EQ(_g1.Get(&Mesh3D::Count),          _g1->Count());
    ASSERT_EQ(_g1.Get(&Mesh3D::Topology),       _g1->Topology());
    ASSERT_EQ(_g1.Get(&Mesh3D::Topology),       PointTopologies::Triangles);
}
TEST_F(_Resource, Properties)
{
    //auto r1 = _l0.Create<Mesh3D>("M1");
    auto m1 = Mesh3D::Cube();
    //auto p1 = Property<PointTopologies, Geometry3D, PointTopologies>(&m1, &Geometry3D::Topology, &Geometry3D::Topology);
    auto p1 = Property<PointTopologies, Geometry3D, PointTopologies>(&m1, &Geometry3D::Topology, &Geometry3D::Topology);
}
TEST_F(_Resource, Set)
{
    ASSERT_EQ(_g1.Get(&Mesh3D::Topology),       PointTopologies::Triangles);
    ASSERT_EQ(_m1.Get(&Material3D::Position),   Vector3::Zero);

    _g1.Set<Geometry3D&, Mesh3D, PointTopologies>(&Mesh3D::Topology, PointTopologies::Lines);
    _m1.Set<Material3D&, Material3D, const Vector3&>(&Material3D::Position, Vector3::One);

    ASSERT_EQ(_g1.Get(&Mesh3D::Topology),       PointTopologies::Lines);
    ASSERT_EQ(_m1.Get(&Material3D::Position),   Vector3::One);
}