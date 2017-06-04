/* CHANGELOG
 * Written by Josh Grooms on 20170526
 */

#include "Math/Constants.h"
#include "Math/Math.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



TEST(_Math, Abs)
{
    constexpr double v1 = Math::Abs(-3.14159265);
    constexpr float v2 = Math::Abs(0.0f);
    constexpr int v3 = Math::Abs(123456789);

    ASSERT_EQ(v1,    3.14159265);
    ASSERT_EQ(v2,    0.0f);
    ASSERT_EQ(v3,    123456789);
}
TEST(_Math, Ceiling)
{
    constexpr float v1  = Math::Ceil(0.0f);
    constexpr double v2 = Math::Ceil(1.0);
    constexpr int v3    = Math::Ceil(-2);
    constexpr float v4  = Math::Ceil(-3.14159f);
    constexpr float v5  = Math::Ceil(3.14159f);
    constexpr double v6 = Math::Ceil(Constants::E<double>);

    ASSERT_EQ(v1,    0.0f);
    ASSERT_EQ(v2,    1.0);
    ASSERT_EQ(v3,    -2);
    ASSERT_EQ(v4,   -3.0f);
    ASSERT_EQ(v5,    4.0f);
    ASSERT_EQ(v6,    3.0);
}
TEST(_Math, Clamping)
{
    constexpr int x = -10;
    constexpr int y = 10;
    constexpr int cx = Math::Clamp(x, -5, 5);
    constexpr int cy = Math::Clamp(y, -5, 5);

    ASSERT_EQ(cx,   -5);
    ASSERT_EQ(cy,    5);
}
TEST(_Math, Comparing)
{
    constexpr int c1 = Math::Compare(-10, 10);
    constexpr int c2 = Math::Compare(200, 2);
    constexpr int c3 = Math::Compare(10, 5 + 5);

    ASSERT_EQ(c1,   -1);
    ASSERT_EQ(c2,    1);
    ASSERT_EQ(c3,    0);
}
TEST(_Math, Extrema)
{
    constexpr int m1 = Math::Max(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
    constexpr int m2 = Math::Max(10, 20, 30, 40, 100, 60, 70, 80, 90, 50);
    constexpr int m3 = Math::Min(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
    constexpr int m4 = Math::Min(50, 20, 30, 40, 10, 60, 70, 80, 90, 100);

    ASSERT_EQ(m1,    100);
    ASSERT_EQ(m2,    m1);
    ASSERT_EQ(m3,    10);
    ASSERT_EQ(m4,    m3);
}
TEST(_Math, Fix)
{
    constexpr float v1 = Math::Fix(Constants::Pi<float>);
    constexpr double v2 = Math::Fix(-Constants::E<double>);

    ASSERT_EQ(v1,    3.0f);
    ASSERT_EQ(v2,   -2.0);
}
TEST(_Math, Floor)
{
    constexpr float v1  = Math::Floor(0.0f);
    constexpr double v2 = Math::Floor(1.0);
    constexpr int v3    = Math::Floor(-2);
    constexpr float v4  = Math::Floor(-3.14159f);
    constexpr float v5  = Math::Floor(3.14159f);
    constexpr double v6 = Math::Floor(Constants::E<double>);

    ASSERT_EQ(v1,    0.0f);
    ASSERT_EQ(v2,    1.0);
    ASSERT_EQ(v3,    -2);
    ASSERT_EQ(v4,   -4.0f);
    ASSERT_EQ(v5,    3.0f);
    ASSERT_EQ(v6,    2.0);
}
TEST(_Math, IsBetween)
{
    constexpr bool v1 = Math::IsBetween(1, 0, 10);
    constexpr bool v2 = Math::IsBetween(1000, 100, 1000000);
    constexpr bool v3 = Math::IsBetween(-20, -21, -19);
    constexpr bool v4 = Math::IsBetween(-1, -5, 10);

    ASSERT_EQ(v1, true);
    ASSERT_EQ(v2, true);
    ASSERT_EQ(v3, true);
    ASSERT_EQ(v4, true);

    constexpr bool v5 = Math::IsBetween(-1, 0, 10);
    constexpr bool v6 = Math::IsBetween(10, 1, 9);
    constexpr bool v7 = Math::IsBetween(-1000000, -10, 30);

    ASSERT_EQ(v5, false);
    ASSERT_EQ(v6, false);
    ASSERT_EQ(v7, false);
}
TEST(_Math, Product)
{
    constexpr int v1 = Math::Product(1, 2, 3, 4);
    constexpr int v2 = Math::Product(10);

    ASSERT_EQ(v1, 24);
    ASSERT_EQ(v2, 10);
}
TEST(_Math, Round)
{
    constexpr float v1  = Math::Round(0.0f);
    constexpr double v2 = Math::Round(1.0);
    constexpr int v3    = Math::Round(-2);
    constexpr float v4  = Math::Round(-3.14159f);
    constexpr float v5  = Math::Round(3.14159f);
    constexpr double v6 = Math::Round(Constants::E<double>);
    constexpr double v7 = Math::Round(-Constants::E<double>);
    constexpr float v8  = Math::Round(10.5f);
    constexpr float v9  = Math::Round(-10.5f);

    ASSERT_EQ(v1,    0.0f);
    ASSERT_EQ(v2,    1.0);
    ASSERT_EQ(v3,   -2);
    ASSERT_EQ(v4,   -3.0f);
    ASSERT_EQ(v5,    3.0f);
    ASSERT_EQ(v6,    3.0);
    ASSERT_EQ(v7,   -3.0);
    ASSERT_EQ(v8,    11.0f);
    ASSERT_EQ(v9,   -11.0f);
}
TEST(_Math, Sign)
{
    constexpr int v1 = Math::Sign(-3.14159265);
    constexpr int v2 = Math::Sign(0.0f);
    constexpr int v3 = Math::Sign(123456789);

    ASSERT_EQ(v1, -1);
    ASSERT_EQ(v2,  1);
    ASSERT_EQ(v3,  1);
}
TEST(_Math, Sqrt)
{
    /*constexpr*/ float v1 = Math::Sqrt(1.0f);
    /*constexpr*/ float v2 = Math::Sqrt(4.0f);
    /*constexpr*/ float v3 = Math::Sqrt(9.0f);
    /*constexpr*/ float v4 = Math::Sqrt(64.0f);

    ASSERT_FLOAT_EQ(v1, 1.0f);
    ASSERT_FLOAT_EQ(v2, 2.0f);
    ASSERT_FLOAT_EQ(v3, 3.0f);
    ASSERT_FLOAT_EQ(v4, 8.0f);

    ASSERT_FLOAT_EQ(Math::Sqrt(64.0f),   8.0f);
}
TEST(_Math, Sum)
{
    constexpr int v1 = Math::Sum(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr int v2 = Math::Sum(-1, -2, -3, -4, -5, -6, -7, -8, -9);

    ASSERT_EQ(v1, 45);
    ASSERT_EQ(v2, -45);

    constexpr int v3 = Math::Sum(1);
    ASSERT_EQ(v3, 1);
}
TEST(_Math, Unfix)
{
    constexpr float v1  = Math::Unfix(0.0f);
    constexpr double v2 = Math::Unfix(1.0);
    constexpr int v3    = Math::Unfix(-2);
    constexpr float v4  = Math::Unfix(-3.14159f);
    constexpr float v5  = Math::Unfix(3.14159f);
    constexpr double v6 = Math::Unfix(Constants::E<double>);

    ASSERT_EQ(v1,    0.0f);
    ASSERT_EQ(v2,    1.0);
    ASSERT_EQ(v3,   -2);
    ASSERT_EQ(v4,   -4.0f);
    ASSERT_EQ(v5,    4.0f);
    ASSERT_EQ(v6,    3.0);
}