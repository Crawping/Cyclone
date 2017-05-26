/* CHANGELOG
 * Written by Josh Grooms on 20170526
 */

#include "Math/Math.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;




TEST(_Utilities, Product)
{
    constexpr int v1 = Math::Product(1, 2, 3, 4);
    ASSERT_EQ(v1, 24);
}