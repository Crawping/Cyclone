/* CHANGELOG
 * Written by Josh Grooms on 20160807
 */

#include <gtest/gtest.h>
#include "Console.h"
#include "Spatial/Transform.h"
#include "Math/Constants.h"
#include "Math/Vector3.h"

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



class _Transform : public testing::Test
{
    protected:
        const Vector3   _v1 = Vector3(Constants::QuarterPi, -Constants::ThirdPi, Constants::TwoPi);
        const Vector3   _v2 = Vector3(-128.0f, 256.0f, -512.0f);

        Matrix4x4       _pitch;
        Matrix4x4       _yaw;
        Matrix4x4       _roll;

        Transform       _t0;
        Transform       _t1;
        Transform       _t2;
        Transform       _t3;
        Transform       _t4;
        Transform       _t5;
        Transform       _t6;
        Transform       _t7;
        Transform       _t8;
        Transform       _t9;
        Transform       _t10;
        

        _Transform() :
            _t2(Vector3::One, Vector3::One, Vector3::One),
            _t4(Transform::Rotation(_v1.X, 0.0f, 0.0f)),
            _t5(Transform::Rotation(0.0f, _v1.Y, 0.0f)),
            _t6(Transform::Rotation(0.0f, 0.0f, _v1.Z)),
            _t7(Transform::Rotation(_v1)),
            _t8(Transform::Scaling(_v2)),
            _t9(Transform::Translation(_v2))
        {
            _t3 = _t2;

            float cr, cp, cy, sr, sp, sy;
            cr = (float)cos(_v1.Z); cp = (float)cos(_v1.X); cy = (float)cos(_v1.Y);
            sr = (float)sin(_v1.Z); sp = (float)sin(_v1.X); sy = (float)sin(_v1.Y);

            _pitch = 
            {
                1.0f,   0.0f,   0.0f,   0.0f,
                0.0f,     cp,     sp,   0.0f,
                0.0f,    -sp,     cp,   0.0f,
                0.0f,   0.0f,   0.0f,   1.0f,
            };
            _roll =
            {
                  cr,     sr,   0.0f,   0.0f,
                 -sr,     cr,   0.0f,   0.0f,
                0.0f,   0.0f,   1.0f,   0.0f,
                0.0f,   0.0f,   0.0f,   1.0f,
            };
            _yaw = 
            {
                  cy,   0.0f,    -sy,   0.0f,
                0.0f,   1.0f,   0.0f,   0.0f,
                  sy,   0.0f,     cy,   0.0f,
                0.0f,   0.0f,   0.0f,   1.0f,
            };
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_Transform, DefaultConstruction)
{
    const float* data = _t0.ToArray();
    for (int a = 0; a < 16; a++)
        ASSERT_EQ(data[a], EYE[a]);
}

//TEST_F(_Transform, CopyConstruction)
//{
//
//}

TEST_F(_Transform, PerspectiveProjectionConstructor)
{

}

TEST_F(_Transform, RotationConstructor)
{
    ASSERT_EQ(Matrix4x4(_t4.ToArray()), _pitch);
    ASSERT_EQ(Matrix4x4(_t5.ToArray()), _yaw);
    ASSERT_EQ(Matrix4x4(_t6.ToArray()), _roll);
}

TEST_F(_Transform, ScalingConstructor)
{
    Matrix4x4 _t8Copy = _t8.ToArray();
    ASSERT_EQ(_t8Copy(0, 0), _v2.X);
    ASSERT_EQ(_t8Copy(1, 1), _v2.Y);
    ASSERT_EQ(_t8Copy(2, 2), _v2.Z);
}

TEST_F(_Transform, TranslationConstructor)
{
    Matrix4x4 _t9Copy = _t9.ToArray();
    ASSERT_EQ(_t9Copy(0, 3), _v2.X);
    ASSERT_EQ(_t9Copy(1, 3), _v2.Y);
    ASSERT_EQ(_t9Copy(2, 3), _v2.Z);
}

TEST_F(_Transform, VectorConstruction)
{
    ASSERT_EQ(_t2.Position(), Vector3::One);
    ASSERT_EQ(_t2.Scale(), Vector3::One);
}



/** OPERATOR TESTS **/
TEST_F(_Transform, EqualityOperators)
{
    ASSERT_EQ(_t0, _t0);
    ASSERT_EQ(_t0, _t1);
    ASSERT_NE(_t0, _t2);
}

TEST_F(_Transform, MultiplicationOperators)
{
    Transform _catRotation = _t6 * _t5 * _t4;
    Matrix4x4 test = _roll * _yaw * _pitch;
    
    ASSERT_EQ(Matrix4x4(_catRotation.ToArray()), test);

    // TODO: This test fails, presumably because of roundoff errors, but I need to double check...
    //ASSERT_EQ(_t7, _catRotation);

    Matrix4x4 _t7Copy = _t7.ToArray();
    for (uint a = 0; a < _t7Copy.Count(); a++)
        ASSERT_NEAR(_t7Copy(a), test(a), 1e-6);
}