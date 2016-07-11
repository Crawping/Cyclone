/* CHANGELOG
 * Written by Josh Grooms on 20160710
 */

#include "Matrix4x4.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
const static float EYE[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};
const static float ONE[16] =
{
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
};
const static float ZERO[16] =
{
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
};



class _Matrix4x4 : public ::testing::Test
{
    protected:
        Matrix4x4 _m0;
        Matrix4x4 _m1;
        Matrix4x4 _m2;
        Matrix4x4 _m3;
        Matrix4x4 _m4;
        

        _Matrix4x4() : 
            _m1(Matrix4x4::Identity),
            _m2(Matrix4x4::One),
            _m3(Matrix4x4::Zero)
            {

            }
};



TEST_F(_Matrix4x4, DefaultConstruction)
{
    ASSERT_EQ(_m0.Count(), 16);
    for (uint a = 0; a < _m0.Count(); a++)
        ASSERT_EQ(_m0(a), EYE[a]);
}

TEST_F(_Matrix4x4, CopyConstruction)
{
    for (uint a = 0; a < _m1.Count(); a++)
    {
        ASSERT_EQ(_m2(a), ONE[a]);
        ASSERT_EQ(_m3(a), ZERO[a]);
    }

    Matrix4x4 _m2Copy(_m2);
    ASSERT_NE(_m2, _m2Copy + 5.0f);
}

TEST_F(_Matrix4x4, EqualityOperators)
{
    ASSERT_EQ(_m0, _m1);
    ASSERT_NE(_m0, _m2);
}

TEST_F(_Matrix4x4, AdditionOperators)
{
    ASSERT_EQ(_m0, _m1 + Matrix4x4::Zero);
    ASSERT_EQ(_m2, _m3 + 1.0f);
}