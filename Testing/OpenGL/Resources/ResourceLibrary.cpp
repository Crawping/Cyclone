/* CHANGELOG 
 * Written by Josh Grooms on 20170606
 */

#include "Geometry/Geometry3D.h"
#include "Geometry/Mesh3D.h"
#include "IO/Functions.h"
#include "Libraries/Resource.h"
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
}
TEST_F(_ResourceLibrary, Destroy)
{
    auto r1 = _l0.Create("G1", Function<Mesh3D, bool>(&Mesh3D::Quad), false);
    ASSERT_EQ(_l0.Count(),          1);
    ASSERT_EQ(r1.IsNull(),          false);
    ASSERT_EQ(r1->Count(),          6);

    auto r2 = _l0.Create<Geometry3D>("G2");

    _l0.Destroy(r1);
    ASSERT_EQ(_l0.Count(),          1);
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

    //auto r7 = _l0.Get<Mesh3D>("G4");
    //ASSERT_EQ(r7,   Resource<Mesh3D>());
}