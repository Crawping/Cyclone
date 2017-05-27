/* CHANGELOG
 * Written by Josh Grooms on 20170526
 */

#include "Math/Math.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



TEST(_Math, Clamping)
{
    constexpr int x = -10;
    constexpr int y = 10;
    constexpr int cx = Math::Clamp(x, -5, 5);
    constexpr int cy = Math::Clamp(y, -5, 5);

    ASSERT_EQ(cx, -5);
    ASSERT_EQ(cy, 5);
}
TEST(_Math, Comparing)
{
    constexpr int c1 = Math::Compare(-10, 10);
    constexpr int c2 = Math::Compare(200, 2);
    constexpr int c3 = Math::Compare(10, 5 + 5);

    ASSERT_EQ(c1, -1);
    ASSERT_EQ(c2, 1);
    ASSERT_EQ(c3, 0);
}
TEST(_Math, Extrema)
{
    constexpr int m1 = Math::Max(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
    constexpr int m2 = Math::Max(10, 20, 30, 40, 100, 60, 70, 80, 90, 50);
    constexpr int m3 = Math::Min(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
    constexpr int m4 = Math::Min(50, 20, 30, 40, 10, 60, 70, 80, 90, 100);

    ASSERT_EQ(m1, 100);
    ASSERT_EQ(m2, m1);
    ASSERT_EQ(m3, 10);
    ASSERT_EQ(m4, m3);
}
TEST(_Math, Product)
{
    constexpr int v1 = Math::Product(1, 2, 3, 4);
    ASSERT_EQ(v1, 24);
}