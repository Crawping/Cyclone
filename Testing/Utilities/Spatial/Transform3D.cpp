/* CHANGELOG
 * Written by Josh Grooms on 20160807
 */

#include <gtest/gtest.h>
#include "IO/Console.h"
#include "Math/Constants.h"
#include "Math/Vector3.h"
#include "Spatial/Transform.h"

using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
struct CanonicalTransforms
{
    Vector3     Orientation;
    Vector3     Position;
    Vector3     Scale;

    Matrix4x4   Pitch;
    Matrix4x4   Yaw;
    Matrix4x4   Roll;

    Matrix4x4   Rotation;
    Matrix4x4   Scaling;
    Matrix4x4   Translation;
    
    Matrix4x4   Transformation;
    


    CanonicalTransforms() : 
        Orientation(Constants::QuarterPi<float>, -Constants::ThirdPi<float>, Constants::TwoPi<float>),
        Position(-128.0f, 256.0f, -512.0f),
        Scale(4.0f, 8.0f, 16.0f)
    {

        // Rotation
        float cr, cp, cy, sr, sp, sy;
        cr = (float)cos(Orientation.Z); cp = (float)cos(Orientation.X); cy = (float)cos(Orientation.Y);
        sr = (float)sin(Orientation.Z); sp = (float)sin(Orientation.X); sy = (float)sin(Orientation.Y);

        Pitch = 
        {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,     cp,     sp,   0.0f,
            0.0f,    -sp,     cp,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
        Roll =
        {
              cr,     sr,   0.0f,   0.0f,
             -sr,     cr,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
        Yaw = 
        {
              cy,   0.0f,    -sy,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
              sy,   0.0f,     cy,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };

        Rotation = Roll * Yaw * Pitch;

        // Scaling
        float w = Scale.X; float h = Scale.Y; float d = Scale.Z;
        Scaling =
        {
               w,   0.0f,   0.0f,   0.0f,
            0.0f,      h,   0.0f,   0.0f,
            0.0f,   0.0f,      d,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };

        // Translation
        float x = Position.X; float y = Position.Y; float z = Position.Z;
        Translation = 
        {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
               x,      y,      z,   1.0f,
        };
               
        // All together
        Transformation = Translation * Roll * Yaw * Pitch * Scaling;
    }
};



/** FIXTURE DEFINITION **/
class _Transform3D : public testing::Test
{
    protected:
        CanonicalTransforms Canon;

        Transform3D _t0;
        Transform3D _t1;
        Transform3D _t2;
        Transform3D _t3;
        Transform3D _t4;
        Transform3D _t5;
        Transform3D _t6;
        Transform3D _t7;
        Transform3D _t8;
        Transform3D _t9;
        Transform3D _t10;
        

        _Transform3D() :
            Canon(),
            _t2(Canon.Position, Canon.Scale, Canon.Orientation),
            _t4(Transform3D::Rotation(Canon.Orientation.X, 0.0f, 0.0f)),
            _t5(Transform3D::Rotation(0.0f, Canon.Orientation.Y, 0.0f)),
            _t6(Transform3D::Rotation(0.0f, 0.0f, Canon.Orientation.Z)),
            _t7(Transform3D::Rotation(Canon.Orientation)),
            _t8(Transform3D::Scaling(Canon.Scale)),
            _t9(Transform3D::Translation(Canon.Position)),
            _t10(Transform3D::Decompose(Canon.Transformation))
        {
            _t3 = _t2;
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_Transform3D, DecompositionConstructor)
{
    ASSERT_EQ(_t10.ToMatrix4x4(), Canon.Transformation);
    ASSERT_EQ(_t10.Position(), Canon.Position);
    ASSERT_EQ(_t10.Scale(), Canon.Scale);

    // No easy way to test for a valid orientation here because there are many possible 
    // solutions that would result in the same overall transformation. 
}
TEST_F(_Transform3D, DefaultConstruction)
{
    ASSERT_EQ(_t0.ToMatrix4x4(), Matrix4x4::Identity);
}
TEST_F(_Transform3D, PerspectiveProjectionConstructor)
{

}
TEST_F(_Transform3D, RotationConstructor)
{
    ASSERT_EQ(_t4.ToMatrix4x4(), Canon.Pitch);
    ASSERT_EQ(_t5.ToMatrix4x4(), Canon.Yaw);
    ASSERT_EQ(_t6.ToMatrix4x4(), Canon.Roll);
    ASSERT_EQ(_t7.ToMatrix4x4(), Canon.Rotation);
}
TEST_F(_Transform3D, ScalingConstructor)
{
    ASSERT_EQ(_t8.ToMatrix4x4(), Canon.Scaling);
}
TEST_F(_Transform3D, TranslationConstructor)
{
    ASSERT_EQ(_t9.ToMatrix4x4(), Canon.Translation);
}
TEST_F(_Transform3D, VectorConstruction)
{
    ASSERT_EQ(_t2.Orientation(),    Canon.Orientation);
    ASSERT_EQ(_t2.Position(),       Canon.Position);
    ASSERT_EQ(_t2.Scale(),          Canon.Scale);

    Matrix4x4 _t2Copy(_t2.ToArray());
    ASSERT_EQ(_t2Copy, Canon.Transformation);
}



/** UTILITIES TESTS **/
TEST_F(_Transform3D, RelativeRotation)
{
    Transform3D _t2Copy(_t2);
    _t2Copy.Rotate(Canon.Orientation).Rotate(Canon.Orientation).Rotate(Canon.Orientation);
    ASSERT_FLOAT_EQ(_t2Copy.Pitch(), 3 * Canon.Orientation.X + _t2.Pitch());
    ASSERT_FLOAT_EQ(_t2Copy.Yaw(),   3 * Canon.Orientation.Y + _t2.Yaw());
    ASSERT_FLOAT_EQ(_t2Copy.Roll(),  3 * Canon.Orientation.Z + _t2.Roll());
}

TEST_F(_Transform3D, RelativeTranslation)
{
    Transform3D _t2Copy(_t2);
    _t2Copy.Translate(Canon.Position).Translate(Canon.Position).Translate(Canon.Position);
    ASSERT_FLOAT_EQ(_t2Copy.X(), 3 * Canon.Position.X + _t2.X());
    ASSERT_FLOAT_EQ(_t2Copy.Y(), 3 * Canon.Position.Y + _t2.Y());
    ASSERT_FLOAT_EQ(_t2Copy.Z(), 3 * Canon.Position.Z + _t2.Z());
}



/** OPERATOR TESTS **/
TEST_F(_Transform3D, EqualityOperators)
{
    ASSERT_EQ(_t0, _t0);
    ASSERT_EQ(_t0, _t1);
    ASSERT_NE(_t0, _t2);
}

TEST_F(_Transform3D, MultiplicationOperators)
{
    Transform3D _catRotation = _t6 * _t5 * _t4;    
    ASSERT_EQ(_catRotation.ToMatrix4x4(), Canon.Rotation);
    ASSERT_EQ(_t7, _catRotation);
}