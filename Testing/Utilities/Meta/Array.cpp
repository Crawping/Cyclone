/* CHANGELOG 
 * Written by Josh Grooms on 20170513
 */

#include "Meta/Array.h"
#include <gtest/gtest.h>
#include <array>

using namespace Cyclone::Utilities;



class _MetaArray : public testing::Test
{
    protected:

        using _a0 = Meta::Array<uint, 0>;
        using _a1 = Meta::Array<uint, 1, 2, 3, 4, 5>;
        using _a2 = _a1::Flip<>;

        using _f1 = Meta::Fill<uint, 10, 0>;
        using _f2 = Meta::Fill<ulong, 32, 100>;
};

class _Range : public testing::Test
{
    protected:
        
        using _r0 = Meta::Range<int, 0, 1>;
        using _r1 = Meta::Range<int, 1, 6>;
        using _r2 = Meta::Range<int, 6, 1>;
};



TEST_F(_MetaArray, Construction)
{
    ASSERT_EQ(_a0::Count(), 1);
    ASSERT_EQ(_a0::First(), 0);
    ASSERT_EQ(_a0::Last(),  0);

    ASSERT_EQ(_a1::Count(), 5);
    ASSERT_EQ(_a1::First(), 1);
    ASSERT_EQ(_a1::Last(),  5);

    ASSERT_EQ(_a2::Count(), 5);
    ASSERT_EQ(_a2::First(), 5);
    ASSERT_EQ(_a2::Last(),  1);

    ASSERT_EQ(_f1::Count(), 10);
    ASSERT_EQ(_f2::Count(), 32);
}
TEST_F(_Range, Construction)
{
    ASSERT_EQ(_r0::Count(), 2);
    ASSERT_EQ(_r1::Count(), 6);
    ASSERT_EQ(_r2::Count(), 6);

    ASSERT_EQ(_r1::First(), 1);
    ASSERT_EQ(_r1::Last(),  6);
    ASSERT_EQ(_r2::First(), 6);
    ASSERT_EQ(_r2::Last(),  1);
}
TEST_F(_MetaArray, Indexing)
{
    constexpr auto f1 = _f1();
    for (uint a = 0; a < _f1::Count(); a++)
        ASSERT_EQ(f1(a), _f1::First());

    constexpr auto f2 = _f2();
    for (uint a = 0; a < _f2::Count(); a++)
        ASSERT_EQ(f2(a), _f2::First());
}
TEST_F(_MetaArray, Subarrays)
{
    constexpr auto a1 = _a1();

    using _s1 = _a1::Remove<3>;
    ASSERT_EQ(_s1::Count(), 2);

    constexpr auto s1 = _s1();
    for (uint a = 0; a < _s1::Count(); a++)
        ASSERT_EQ(s1(a), a1(a + 3));

    using _s2 = _a1::Take<3>;
    ASSERT_EQ(_s2::Count(), 3);

    constexpr auto s2 = _s2();
    for (uint a = 0; a < _s2::Count(); a++)
        ASSERT_EQ(s2(a), a1(a));

    using _s3 = _a1::Slice<1, 3>;
    ASSERT_EQ(_s3::Count(), 3);

    constexpr auto s3 = _s3();
    for (uint a = 0; a < _s3::Count(); a++)
        ASSERT_EQ(s3(a), a1(a + 1));
}
TEST_F(_Range, Indexing)
{
    auto r1 = _r1();
    for (uint a = 0; a < _r1::Count(); a++)
        ASSERT_EQ(r1(a), _r1::First() + a);

    auto r2 = _r2();
    for (uint a = 0; a < _r2::Count(); a++)
        ASSERT_EQ(r2(a), _r2::First() - a);
}