
#include "Geometry/Vertex.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;



class _Vertex: public testing::Test
{
    protected:
        
        Vertex _v0;
        Vertex _v1;


        _Vertex(): 
            _v1(Vector3::Zero, Vector3::Zero, Vector2::Zero)
        {

        }
};



TEST_F(_Vertex, Attributes)
{
    auto a1 = Vertex::Layout();
    ASSERT_EQ(a1.Count(), 3);
}
TEST_F(_Vertex, Construction)
{
    ASSERT_EQ(_v0.Position, Vector3::Zero);
    ASSERT_EQ(_v0.Normal,   Vector3::Zero);
}

TEST_F(_Vertex, VertexLayouts)
{
    //ASSERT_EQ(_a1.Count(), 1);

    //ASSERT_EQ(_a1(0).Count, 3);
    //ASSERT_EQ(_a1(0).Format, NumericFormats::Float);
    //ASSERT_EQ(_a1(0).Offset, offsetof(Vertex::Simple, Position));

    //ASSERT_EQ(_a2.Count(), 3);
    //ASSERT_EQ(_a2(0).Count, 3);
    //ASSERT_EQ(_a2(0).Format, NumericFormats::Float);
    //ASSERT_EQ(_a2(0).Offset, offsetof(Vertex, Position));

    //ASSERT_EQ(_a2(1).Count, 3);
    //ASSERT_EQ(_a2(1).Offset, offsetof(Vertex, Normal));
}
