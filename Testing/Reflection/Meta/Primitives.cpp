/* CHANGELOG
 * Written by Josh Grooms on 20170421
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Meta/String.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;



TEST(_Primitives, Functions)
{
    using fcn = Meta::Function<void, Color4, ulong, Vector4, Vector4>;
    ASSERT_EQ(fcn::Inputs::Count(),   4);

    Meta::IsEqual<fcn::Inputs::Get<1>::Type, ulong> c1;
    ASSERT_TRUE(c1);

    Meta::IsEqual<fcn::Output, void> c2;
    ASSERT_TRUE(c2);
}
TEST(_Primitives, Lists)
{
    using L1 = Meta::List<uint, Color4, double, Vector4>;

    ASSERT_EQ((L1::Count()),    4);
    
    Meta::IsEqual<L1::Get<3>::Type, Vector4> c1;
    ASSERT_TRUE(c1);

    uint x = 0;
    auto y = L1::Cast<3>(x);

    ASSERT_TRUE(Meta::TypeEquals<Vector4>(y));
    ASSERT_FALSE(Meta::TypeEquals<Color4>(y));
}
TEST(_Primitives, Strings)
{
    using S1 = Meta::String<'T', 'E', 'S', 'T', 'I', 'N', 'G'>;
    ASSERT_EQ(S1::Count(),      7);
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