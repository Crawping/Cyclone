/* CHANGELOG
 * Written by Josh Grooms on 20170513
 */

#include "Collections/Array.h"
#include "Math/Constants.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Array : public testing::Test
{
    protected:
        
        Array<uint, 1>          _a10;
        Array<uint, 1, 1>       _a20;
        Array<uint, 1, 1, 1>    _a30;
        Array<uint, 1, 2, 3>    _a31;
        Array<double, 3, 3, 3>  _a32;

        Array<double, 10, 20, 30, 40> _a40;
        Array<float, 5, 6, 7, 8, 9, 10> _a61;

        constexpr const static uint _u61[] = { 1, 2, 3, 4, 5, 6 };


        _Array():
            _a31(_u61)
        {
            for (uint a = 0; a < _a32.Count(); a++)
                _a32(a) = a + 1;

            for (uint a = 0; a < _a61.Count(); a++)
                _a61(a) = _a61.Count() - a;
        }
};



TEST_F(_Array, Construction)
{
    ASSERT_EQ(_a10.Count(), 1);
    ASSERT_EQ(_a20.Count(), 1);
    ASSERT_EQ(_a30.Count(), 1);

    ASSERT_EQ(_a10.Rank(),  1);
    ASSERT_EQ(_a20.Rank(),  2);
    ASSERT_EQ(_a30.Rank(),  3);

    ASSERT_EQ(_a31.Count(), 6);
    ASSERT_EQ(_a31.Rank(),  3);

    ASSERT_EQ(_a32.Count(), 27);
    ASSERT_EQ(_a32.Rank(),  3);

    ASSERT_EQ(_a40.Count(), Meta::Product(10, 20, 30, 40));
    ASSERT_EQ(_a40.Rank(),  4);

    auto size = _a61.Size();
    ASSERT_EQ(size.Count(), 6);
    for (uint a = 0; a < size.Count(); a++)
        ASSERT_EQ(size(a), a + 5);
}
TEST_F(_Array, Flattening)
{
    Array<double, 27> a32 = _a32.Flatten();
    for (uint a = 0; a < _a32.Count(); a++)
        ASSERT_EQ(a32(a), _a32(a));
}
TEST_F(_Array, Indexing)
{
    constexpr Array<int, 3, 2, 1> a2 = { 1, 2, 3, 4, 5, 6 };
    constexpr int v1 = a2(2, 1, 0);
    ASSERT_EQ(v1, 6);

    for (uint a = 0; a < _a30.Count(); a++)
        ASSERT_EQ(_a30(a), 0);

    for (uint a = 0; a < 6; a++)
        ASSERT_EQ(_a31(a), _u61[a]);

    for (uint a = 0; a < _a31.Size(0); a++)
        for (uint b = 0; b < _a31.Size(1); b++)
            for (uint c = 0; c < _a31.Size(2); c++)
                ASSERT_EQ(_a31(a, b, c), c * 2 + b + a + 1);

    for (uint a = 0; a < _a32.Size(0); a++)
        for (uint b = 0; b < _a32.Size(1); b++)
            for (uint c = 0; c < _a32.Size(2); c++)
                ASSERT_EQ(_a32(a, b, c), c * 3 * 3 + b * 3 + a + 1);

    float idx = _a61.Count();
    for (uint f = 0; f < _a61.Size(5); f++)
        for (uint e = 0; e < _a61.Size(4); e++)
            for (uint d = 0; d < _a61.Size(3); d++)
                for (uint c = 0; c < _a61.Size(2); c++)
                    for (uint b = 0; b < _a61.Size(1); b++)
                        for (uint a = 0; a < _a61.Size(0); a++)
                            ASSERT_EQ(_a61(a, b, c, d, e, f), idx--);

    for (uint a = 0; a < a2.Count(); a++)
        ASSERT_EQ(a2(a), a + 1);
}
TEST_F(_Array, IndexByArray)
{
    constexpr Array<uint, 3, 2, 1> a1 = _u61;
    constexpr Array<uint, 3> ids = { 1, 3, 5 };
    constexpr const auto a2 = a1(ids);
    ASSERT_EQ(a2.Count(), 3);

    for (uint a = 0; a < a2.Count(); a++)
        ASSERT_EQ(a2(a), ids(a) + 1);
}