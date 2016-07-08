/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#include <gtest/gtest.h>
#include "Vector2.h"

using namespace Cyclone::Utilities;



class _Vector2 : public ::testing::Test
{
    protected:

        Vector2 _v0;
        Vector2 _v1;
        Vector2 _v2;
        Vector2 _v3;

        _Vector2() :
            _v1(Vector2::Zero),
            _v2(Vector2::One),
            _v3(-32.64f, 128.256f)
        {

        }
};



TEST_F(_Vector2, ObjectConstruction)
{
    ASSERT_EQ(_v0.X, 0.0f);     ASSERT_EQ(_v0.Y, 0.0f);
    ASSERT_EQ(_v1.X, 0.0f);     ASSERT_EQ(_v1.Y, 0.0f);
    ASSERT_EQ(_v2.X, 1.0f);     ASSERT_EQ(_v2.Y, 1.0f);
    ASSERT_EQ(_v3.X, -32.64f);  ASSERT_EQ(_v3.Y, 128.256f);
}

TEST_F(_Vector2, EqualityOperators)
{
    ASSERT_EQ(_v0, _v1);
    ASSERT_NE(_v0, _v2);
}

TEST_F(_Vector2, VectorTranslation)
{
    const Vector2 result(-31.64f, 129.256f);

    Vector2 _v3Copy(_v3);
    ASSERT_EQ(_v3Copy.Translate(Vector2::Zero), _v3);
    ASSERT_EQ(_v3Copy.Translate(Vector2::One), result);

    ASSERT_EQ(_v3Copy -= 1.0f, _v3);
    ASSERT_EQ(_v3Copy += Vector2::One, result);
}

TEST_F(_Vector2, MathOperators)
{
    ASSERT_EQ(_v3 + 5.0f, Vector2(_v3.X + 5.0f, _v3.Y + 5.0f));
    ASSERT_EQ(_v3 + -25.0f, _v3 - 25.0f);
    ASSERT_EQ(_v3 + Vector2(-12.67f), _v3 - Vector2(12.67f));

    ASSERT_EQ(_v3 / 3.14159f, Vector2(_v3.X / 3.14159f, _v3.Y / 3.14159f));
    ASSERT_EQ(_v3 / 3.14159f, _v3 * (1.0f / 3.14159f));
    ASSERT_EQ(_v3 / Vector2(3.14159), _v3 * (1.0f / Vector2(3.14159f)));
}