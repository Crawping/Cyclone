/* CHANGELOG
 * Written by Josh Grooms on 20160807
 */

#include <gtest/gtest.h>
#include "Spatial/Transform.h"
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
        Transform _t0;
        Transform _t1;
        Transform _t2;
        Transform _t3;
        

        _Transform() :
            _t2(Vector3::One, Vector3::One, Vector3::One)
        {
            _t3 = _t2;
        }

};




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


TEST_F(_Transform, VectorConstruction)
{
    ASSERT_EQ(_t2.Position(), Vector3::One);
    ASSERT_EQ(_t2.Scale(), Vector3::One);
}
TEST_F(_Transform, EqualityOperators)
{
    ASSERT_EQ(_t0, _t0);
    ASSERT_EQ(_t0, _t1);
    ASSERT_NE(_t0, _t2);
}