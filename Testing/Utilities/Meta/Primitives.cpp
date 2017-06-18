/* CHANGELOG
 * Written by Josh Grooms on 20170421
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Meta/Function.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



TEST(_Primitives, Functions)
{
    using fcn = Meta::Function<void, Color4, ulong, Vector4, Vector4>;
    ASSERT_EQ(fcn::Inputs::Count,   4);

    Meta::IsEqual<fcn::Inputs::Get<1>, ulong> c1;
    ASSERT_TRUE(c1);

    Meta::IsEqual<fcn::Output, void> c2;
    ASSERT_TRUE(c2);
}

//TEST(_Primitives, Primitives)
//{
//    //ASSERT_EQ((Meta::Primitive<Color4, Color4()>()),        Color4());
//}
//TEST(_Primitives, Numbers)
//{
//    ASSERT_EQ((Meta::Number<byte, 'a'>::Precision()),       8);
//    ASSERT_EQ((Meta::Number<byte, 'a'>::Precision()),       8);
//
//    ASSERT_TRUE((Meta::Number<uint, 128>::Precision()),     32);
//}