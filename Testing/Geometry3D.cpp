/* CHANGELOG
 * Written by Josh Grooms on 20160816
 */

//#include "Spatial/Geometry.h"
#include "Geometry/Geometry3D.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
struct CanonicalGeometry3D
{
    public:
        Vector<uint> CubeIndices;


        CanonicalGeometry3D() :
            CubeIndices(36)
        {
            CubeIndices =
            {
                0,	 1,	 2,	 2,	 1,	 3,
                4,	 5,	 6,	 6,	 5,	 7,
                8,	 9, 10, 10,  9, 11,
                12, 13, 14, 14, 13, 15,
                16, 17, 18, 18, 17, 19,
                20, 21, 22, 22, 21, 23,
            };
        }
};



/** FIXTURE DEFINITION **/
class _Geometry3D : public testing::Test
{

    protected:
        CanonicalGeometry3D   Canon;

        Vector<uint>             CubeIndices;
        Vector<Vertex::Standard> CubeVertices;

        _Geometry3D() :
            Canon(),
            CubeIndices(36),
            CubeVertices(36)
        {
            CubeVertices = Geometry3D::Cube(CubeIndices);
        }

};



/** TESTS **/
TEST_F(_Geometry3D, CubeTests)
{
    ASSERT_EQ(CubeIndices, Canon.CubeIndices);
}