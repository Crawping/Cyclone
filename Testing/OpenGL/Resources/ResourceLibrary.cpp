/* CHANGELOG 
 * Written by Josh Grooms on 20170606
 */

#include "Geometry/Geometry3D.h"
#include "Geometry/Mesh3D.h"
#include "Libraries/Material3D.h"
#include "Resources/ResourceLibrary2.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;



class _ResourceLibrary: public testing::Test
{
    protected:

        ResourceLibrary2 _l0;


        _ResourceLibrary()
        {

        }

};


TEST_F(_ResourceLibrary, Construction)
{
    ASSERT_EQ(_l0.Count(), 0);
}
TEST_F(_ResourceLibrary, Contains)
{
    auto r1 = _l0.Create<Mesh3D>("G1");
    auto r2 = _l0.Create<Geometry3D>("G2");
    auto r3 = Resource<IGeometric>("G1", nullptr);

    ASSERT_EQ(_l0.Contains(r1),     true);
    ASSERT_EQ(_l0.Contains(r2),     true);
    ASSERT_EQ(_l0.Contains(r3),     false);
}
TEST_F(_ResourceLibrary, Create)
{
    auto r1 = _l0.Create<Mesh3D>("G1");
    ASSERT_EQ(_l0.Count(),          1);
    ASSERT_EQ(_l0.GeometryCount(),  1);
    ASSERT_EQ(r1.Name(),            "G1");
    ASSERT_EQ(r1->IsEmpty(),        true);
    ASSERT_EQ(r1->Count(),          0);

    auto r2 = _l0.Create("G2", Function<Mesh3D, bool>(&Mesh3D::Cube), true);
    ASSERT_EQ(_l0.Count(),          2);
    ASSERT_EQ(_l0.GeometryCount(),  2);
    ASSERT_EQ(r2.Name(),            "G2");
    ASSERT_EQ(r2->IsEmpty(),        false);
    ASSERT_EQ(r2->IsIndexed(),      true);
    ASSERT_EQ(r2->Count(),          36);

    auto r3 = _l0.Create("G3", Constructor<Geometry3D>());
    ASSERT_EQ(r3->IsEmpty(),        true);
    ASSERT_EQ(r3->IsIndexed(),      false);

    auto m1 = _l0.Create<Material3D>("M1");
    ASSERT_EQ(_l0.Count(),          4);
    ASSERT_EQ(_l0.GeometryCount(),  3);
    ASSERT_EQ(_l0.MaterialCount(),  1);
}
TEST_F(_ResourceLibrary, Destroy)
{
    auto r1 = _l0.Create("G1", Function<Mesh3D, bool>(&Mesh3D::Quad), false);
    ASSERT_EQ(_l0.GeometryCount(),  1);
    ASSERT_EQ(r1.IsNull(),          false);
    ASSERT_EQ(r1->Count(),          6);

    auto r2 = _l0.Create<Geometry3D>("G2");
    ASSERT_EQ(_l0.GeometryCount(),  2);

    _l0.Destroy(r1);
    ASSERT_EQ(_l0.GeometryCount(),  1);
    _l0.Destroy(r2);
    ASSERT_EQ(_l0.GeometryCount(),  0);

    auto m1 = _l0.Create<Material3D>("M1");
    ASSERT_EQ(_l0.GeometryCount(),  0);
    ASSERT_EQ(_l0.MaterialCount(),  1);

    _l0.Destroy(m1);
    ASSERT_EQ(_l0.MaterialCount(),  0);
}
TEST_F(_ResourceLibrary, Get)
{
    auto r1 = _l0.Create<Mesh3D>("G1", Function<Mesh3D, bool>(&Mesh3D::Cube), true);
    auto r2 = _l0.Create<Mesh3D>("G2", Function<Mesh3D, bool>(&Mesh3D::Quad), false);
    auto r3 = _l0.Create<Geometry3D>("G3");

    auto r4 = _l0.Get<Mesh3D>("G1");
    auto r5 = _l0.Get<Mesh3D>("G2");
    auto r6 = _l0.Get<Geometry3D>("G3");

    ASSERT_EQ(r1, r4);
    ASSERT_EQ(r2, r5);
    ASSERT_EQ(r3, r6);

    ASSERT_NE(r1, r5);
    ASSERT_NE(r1, r6);
    ASSERT_NE(r2, r6);

    auto r7 = _l0.Get<Mesh3D>("G4");
    ASSERT_EQ(r7.IsNull(), true);

    ASSERT_EQ(r1.Get(&Mesh3D::Count),       r1->Count());
    ASSERT_EQ(r1.Get(&Mesh3D::Topology),    r1->Topology());
    ASSERT_EQ(r1.Get(&Mesh3D::Topology),    PointTopologies::Triangles);
}
TEST_F(_ResourceLibrary, Set)
{
    auto r1 = _l0.Create<Mesh3D>("G1", Constructor<Mesh3D>());
    ASSERT_EQ(r1.Get(&Mesh3D::Topology), PointTopologies::Triangles);

    r1.Set<Geometry3D&, Mesh3D, PointTopologies>(&Mesh3D::Topology, PointTopologies::Lines);
    ASSERT_EQ(r1.Get(&Mesh3D::Topology), PointTopologies::Lines);

    auto m1 = _l0.Create<Material3D>("M1");
    ASSERT_EQ(m1.Get(&Material3D::Position), Vector3::Zero);

    m1.Set<Material3D&, Material3D, const Vector3&>(&Material3D::Position, Vector3::One);
    ASSERT_EQ(m1.Get(&Material3D::Position), Vector3::One);
}