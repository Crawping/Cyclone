/* */

#include "Constants.h"
#include "Vector3.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Vector3 : public ::testing::Test
{
    protected:

        Vector3 _v0;
        Vector3 _v1;
        Vector3 _v2;
        Vector3 _v3;

        _Vector3() :
            _v1(Vector3::Zero),
            _v2(Vector3::One),
            _v3(-128.256f, 1024.2048f, -32.64f)
        {
            
        }
};



TEST_F(_Vector3, ObjectConstruction)
{
    ASSERT_EQ(_v1.X, 0.0f);         ASSERT_EQ(_v1.X, 0.0f);         ASSERT_EQ(_v1.Z, 0.0f);
    ASSERT_EQ(_v2.X, 1.0f);         ASSERT_EQ(_v2.Y, 1.0f);         ASSERT_EQ(_v2.Z, 1.0f);
    ASSERT_EQ(_v3.X, -128.256f);    ASSERT_EQ(_v3.Y, 1024.2048f);   ASSERT_EQ(_v3.Z, -32.64f);
}

TEST_F(_Vector3, EqualityOperators)
{
    ASSERT_EQ(_v0, _v1);
    ASSERT_NE(_v1, _v2);
}

TEST_F(_Vector3, MathOperators)
{
    ASSERT_EQ(_v3 + 5.0f, Vector3(_v3.X + 5.0f, _v3.Y + 5.0f, _v3.Z + 5.0f));
    ASSERT_EQ(_v3 + -25.0f, _v3 - 25.0f);
    ASSERT_EQ(_v3 + Vector3(-12.67f), _v3 - Vector3(12.67f));

    ASSERT_EQ(_v3 / (float)Constants::Pi, Vector3(_v3.X / (float)Constants::Pi, _v3.Y / (float)Constants::Pi, _v3.Z / (float)Constants::Pi));
}

TEST_F(_Vector3, VectorTranslation)
{
    const Vector3 result = _v3 + Vector3::One;

    Vector3 _v3Copy(_v3);
    ASSERT_EQ(_v3Copy.Translate(Vector3::Zero), _v3);
    ASSERT_EQ(_v3Copy.Translate(Vector3::One), result);

    ASSERT_EQ(_v3Copy -= 1.0f, _v3);
    ASSERT_EQ(_v3Copy += Vector3::One, result);
}