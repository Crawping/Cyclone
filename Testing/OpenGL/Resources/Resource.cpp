/* CHANGELOG
 * Written by Josh Grooms on 20170608
 */

#include "Geometry/Mesh3D.h"
#include "IO/Members.h"
#include "Libraries/Material3D.h"
#include "Resources/Resource.h"
#include "Resources/ResourceLibrary2.h"
#include "Textures/Texture3D.h"
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

        Attribute<Geometry3D, PointTopologies>  _p1;
        Attribute<Material3D, const Color4&>    _p2;


        _Resource():
            _g1(_l0.Create<Mesh3D>("G1")),
            _g2(_l0.Create<Mesh3D>("G2", Constructor<Mesh3D>())),
            _g3(_l0.Create<Mesh3D>("G3", Function<Mesh3D, bool>(&Mesh3D::Cube), true)),
            _m1(_l0.Create<Material3D>("M1")),
            _p1(&Mesh3D::Topology, &Mesh3D::Topology),
            _p2(&Material3D::PrimaryColor, &Material3D::PrimaryColor)
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
    ASSERT_EQ(_g1[_p1],                     PointTopologies::Triangles);
    ASSERT_EQ(_m1[_p2],                     Color4::Black);
}
TEST_F(_Resource, Set)
{
    _g1[_p1] = PointTopologies::Lines;
    _m1[_p2] = Color4::White;

    ASSERT_EQ(_g1[_p1],                     PointTopologies::Lines);
    ASSERT_EQ(_m1[_p2],                     Color4::White);
}
TEST_F(_Resource, Upcast)
{
    Resource<IMaterial> m1 = _m1;
    Attribute<IMaterial, const Color4&> p2(&IMaterial::PrimaryColor, nullptr);
    ASSERT_EQ(m1[p2],                       Color4::Black);
}