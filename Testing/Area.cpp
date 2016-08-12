/* CHANGELOG
 * Written by Josh Grooms on 20160811
 */

#pragma once
#include "Utilities.h"
#include "Math/Vector4.h"
#include "Spatial/Area.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace Cyclone::Utilities;



class _Area : public testing::Test
{
    protected:
        const Vector4 _v1 = Vector4(16.32f, -64.128f, 256.512f, 1024.2048f);
        const Vector4 _v2 = Vector4(4.8f, 0.0f, 512.1024f, 128.256f);

        const Vector2 _p1 = Vector2(0.5f, 0.25f);
        const Vector2 _p2 = Vector2(32.0f, 64.0f);
        
        Area _a0;
        Area _a1;
        Area _a2;
        Area _a3;


        _Area() : 
            _a1(Area::Unit),
            _a2(_v1.X, _v1.Y, _v1.Z, _v1.W),
            _a3(_v2.X, _v2.Y, _v2.Z, _v2.W)
        {
            
        }

};



/** CONSTRUCTOR TESTS **/
TEST_F(_Area, DefaultConstruction)
{
    ASSERT_EQ(_a0.X,        0.0f);
    ASSERT_EQ(_a0.Y,        0.0f);
    ASSERT_EQ(_a0.Width,    0.0f);
    ASSERT_EQ(_a0.Height,   0.0f);
}

TEST_F(_Area, ObjectConstruction)
{
    ASSERT_EQ(_a2.X,        _v1.X);
    ASSERT_EQ(_a2.Y,        _v1.Y);
    ASSERT_EQ(_a2.Width,    _v1.Z);
    ASSERT_EQ(_a2.Height,   _v1.W);
}



/** PROPERTY TESTS **/
TEST_F(_Area, Properties)
{
    ASSERT_EQ(_a2.Bottom(), _v1.Y);
    ASSERT_EQ(_a2.Left(),   _v1.X);
    ASSERT_EQ(_a2.Right(),  _v1.X + _v1.Z);
    ASSERT_EQ(_a2.Top(),    _v1.Y + _v1.W);
}



/** UTILITY TESTS **/
TEST_F(_Area, AreaContainment)
{
    ASSERT_FALSE(_a3.Contains(_a1));
    ASSERT_FALSE(_a3.Contains(_a2));
    ASSERT_FALSE(_a2.Contains(_a3));
}

TEST_F(_Area, PointContainment)
{
    ASSERT_TRUE(_a1.Contains(_p1));
    ASSERT_TRUE(_a2.Contains(_p2));
    ASSERT_TRUE(_a3.Contains(_p2));

    ASSERT_FALSE(_a1.Contains(_p2));
    ASSERT_FALSE(_a2.Contains(_p1));
    ASSERT_FALSE(_a3.Contains(_p1));
}

TEST_F(_Area, Cropping)
{
    _a2.Crop(_a3);
    ASSERT_EQ(_a2.Left(),   fmaxf(_a2.Left(), _a3.Left()));
    ASSERT_EQ(_a2.Bottom(), fmaxf(_a2.Bottom(), _a3.Bottom()));
    ASSERT_EQ(_a2.Right(),  fminf(_a2.Right(), _a3.Right()));
    ASSERT_EQ(_a2.Top(),    fminf(_a2.Top(), _a3.Top()));
}

TEST_F(_Area, Flipping)
{
    Area _a2Copy = Area(_a2).Flip(1);
    ASSERT_FLOAT_EQ(_a2Copy.Left(),     _a2.Right());
    ASSERT_FLOAT_EQ(_a2Copy.Right(),    _a2.Left());
    ASSERT_FLOAT_EQ(_a2Copy.Width,     -_a2.Width);

    _a2Copy = Area(_a2).Flip(2);
    ASSERT_FLOAT_EQ(_a2Copy.Bottom(),   _a2.Top());
    ASSERT_FLOAT_EQ(_a2Copy.Top(),      _a2.Bottom());
    ASSERT_FLOAT_EQ(_a2Copy.Height,    -_a2.Height);
}


/** OPERATOR TESTS **/
TEST_F(_Area, EqualityOperators)
{
    ASSERT_EQ(_a0, Area::Empty);
    ASSERT_EQ(_a1, Area::Unit);
    ASSERT_NE(_a0, _a1);
}

