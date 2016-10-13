
#include "Geometry/Vertex.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;


class _Vertex : public testing::Test
{
    protected:
        
        Vertex::Simple _v0;
        Vector<VertexAttribute> _a1;
        Vector<VertexAttribute> _a2;



        _Vertex() : 
            _a1(Vertex::Simple().Layout()),
            _a2(Vertex::Standard().Layout())
        {

        }
};



TEST_F(_Vertex, DefaultConstruction)
{
    ASSERT_EQ(_v0.Position, Vector3::Zero);

    ASSERT_EQ(sizeof(Vertex::Simple), sizeof(Vector3) + sizeof(IVertex));
}

TEST_F(_Vertex, VertexLayouts)
{
    ASSERT_EQ(_a1.Count(), 1);

    ASSERT_EQ(_a1(0).Count, 3);
    ASSERT_EQ(_a1(0).Format, NumericFormats::Float);
    ASSERT_EQ(_a1(0).Offset, offsetof(Vertex::Simple, Position));

    ASSERT_EQ(_a2.Count(), 3);
    ASSERT_EQ(_a2(0).Count, 3);
    ASSERT_EQ(_a2(0).Format, NumericFormats::Float);
    ASSERT_EQ(_a2(0).Offset, offsetof(Vertex::Standard, Position));

    ASSERT_EQ(_a2(1).Count, 3);
    ASSERT_EQ(_a2(1).Offset, offsetof(Vertex::Standard, Normal));
}
