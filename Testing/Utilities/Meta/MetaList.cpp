/* CHANGELOG 
 * Written by Josh Grooms on 20170425
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Meta/Function.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _MetaList : public testing::Test 
{
    protected:

        using L1 = Meta::List<uint, Color4, double, Vector4>;
        using L2 = L1::Concatenate<char, int, ulong*>;
};



TEST_F(_MetaList, Construction)
{
    ASSERT_EQ(L1::Count,    4);
    ASSERT_EQ(L1::Size,     sizeof(uint) + sizeof(Color4) + sizeof(double) + sizeof(Vector4));
    
    ASSERT_TRUE(( Meta::IsEqual<L1::Get<3>, Vector4>() ));
}


TEST_F(_MetaList, Concatenation)
{
    ASSERT_EQ(L2::Count,    7);
    ASSERT_EQ(L2::Size,     sizeof(uint) + sizeof(Color4) + sizeof(double) + sizeof(Vector4) + sizeof(char) + sizeof(int) + sizeof(ulong*));

    ASSERT_TRUE(( Meta::IsEqual<L2::First::Type, L1::First::Type>() ));
    ASSERT_TRUE(( Meta::IsEqual<L2::Last::Type, ulong*>() ));
}