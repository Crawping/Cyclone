/* CHANGELOG 
 * Written by Josh Grooms on 20170423
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;



TEST(_Class, Properties)
{
    using c1 = Meta::Class<int>;
    using c2 = Meta::Class<int*>;
    using c3 = Meta::Class<const int*>;
    using c4 = Meta::Class<const string&>;

    ASSERT_FALSE(( c1::IsConstant() ));
    ASSERT_FALSE(( c1::IsPointer() ));
    ASSERT_FALSE(( c1::IsReference() ));

    ASSERT_FALSE(( c2::IsConstant() ));
    ASSERT_FALSE(( c2::IsReference() ));
    ASSERT_TRUE((  c2::IsPointer() ));

    ASSERT_TRUE(( c3::IsConstant() ));
    ASSERT_TRUE(( c3::IsPointer() ));

    ASSERT_TRUE(( c4::IsConstant() ));
    ASSERT_TRUE(( c4::IsReference() ));
    ASSERT_FALSE(( c4::IsPointer() ));

    ASSERT_TRUE(( Meta::IsEqual<c4::Type, string>() ));
    ASSERT_TRUE(( Meta::IsEqual<c4::CoreType::Type, string>() ));

    Meta::IsEqual
    < 
        Meta::Class<const string&>
            ::IsConstant
            ::IsConstant
            ::IsConstant
            ::IsConstant
            ::Type, 
        bool
    > check1;

    ASSERT_TRUE(check1);
}
TEST(_Class, Inheritance)
{
    using c1 = Meta::Class<int>;
    using c2 = Meta::Class<const int*>;


}