
#include "Geometry/Vertices.h"
#include <gtest/gtest.h>

using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;


class _Vertices : public testing::Test
{
    protected:
        
        Vertex::Simple _v0;



        _Vertices()
        {

        }
};



TEST_F(_Vertices, DefaultConstruction)
{
    ASSERT_EQ(_v0.Position, Vector3::Zero);
    ASSERT_EQ(_v0.UV, Vector2::Zero);

    ASSERT_EQ(sizeof(Vertex::Simple), sizeof(Vector3) + sizeof(Vector2) + sizeof(IVertex));
}

TEST_F(_Vertices, VertexLayouts)
{
    auto layout = _v0.Layout();
    ASSERT_EQ(layout.Count(), 2);

    ASSERT_EQ(layout(0).Count, 3);
    ASSERT_EQ(layout(0).Format, NumericFormats::Float);
    ASSERT_EQ(layout(0).Offset, offsetof(Vertex::Simple, Position));

    ASSERT_EQ(layout(1).Count, 2);
    ASSERT_EQ(layout(1).Offset, offsetof(Vertex::Simple, UV));
}
