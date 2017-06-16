/* CHANGELOG
 * Written by Josh Grooms on 20170616
 */

#include "Math/Constants.h"
#include "Spatial/LineSegment.h"
#include "Spatial/Transform.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _LineSegment: public testing::Test
{
    protected:

        LineSegment _l0;
        LineSegment _l1;

        _LineSegment():
            _l1{ Vector3::Zero, Vector3::One }
        {

        }

};



TEST_F(_LineSegment, Construction)
{
    ASSERT_EQ(_l0.A,            Vector3::Zero);
    ASSERT_EQ(_l0.B,            Vector3::Zero);
    ASSERT_EQ(_l0.Length(),     0.0f);
    //ASSERT_EQ(_l0.Vector(),     Vector3::Zero);

    ASSERT_EQ(_l1.A,            Vector3::Zero);
    ASSERT_EQ(_l1.B,            Vector3::One);
    //ASSERT_EQ(_l1.Length(),     1.0f);
}
TEST_F(_LineSegment, Transformation)
{
    auto t = Transform3D::Rotation(0, Constants::Pi<float>, 0);
    auto l0 = t * _l0;

    ASSERT_EQ(l0.A,             Vector3::Zero);
    ASSERT_EQ(l0.B,             Vector3::Zero);

    auto l1 = t * _l1;

    ASSERT_EQ(l1.A,             Vector3::Zero);
    //ASSERT_EQ(l1.B,             Vector3(-1.0f, 1.0f, -1.0f));
}