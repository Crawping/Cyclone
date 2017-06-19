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
        
        Array<uint, 1>                  _a10;
        Array<uint, 1, 1>               _a20;
        Array<uint, 1, 1, 1>            _a30;
        Array<uint, 1, 2, 3>            _a31;
        Array<double, 3, 3, 3>          _a32;

        Array<double, 10, 20, 30, 40>   _a40;
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

    ASSERT_EQ(_a40.Count(), Math::Product(10, 20, 30, 40));
    ASSERT_EQ(_a40.Rank(),  4);
}
TEST_F(_Array, Counts)
{
    using A61 = Array<float, 5, 6, 7, 8, 9, 10>;
    constexpr uint c1 = A61::Count(0);
    constexpr uint c2 = A61::Count(1);
    constexpr uint c3 = A61::Count(2);
    constexpr uint c4 = A61::Count(3);
    constexpr uint c5 = A61::Count(4);
    constexpr uint c6 = A61::Count(5);

    ASSERT_EQ(c1, 5);
    ASSERT_EQ(c1, Math::Product(5));
    ASSERT_EQ(c2, Math::Product(5, 6));
    ASSERT_EQ(c3, Math::Product(5, 6, 7));
    ASSERT_EQ(c4, Math::Product(5, 6, 7, 8));
    ASSERT_EQ(c5, Math::Product(5, 6, 7, 8, 9));
    ASSERT_EQ(c6, Math::Product(5, 6, 7, 8, 9, 10));
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
    constexpr const auto a2 = a1[ids];
    ASSERT_EQ(a2.Count(), 3);

    for (uint a = 0; a < a2.Count(); a++)
        ASSERT_EQ(a2(a), ids(a) + 1);
}
TEST_F(_Array, IndexOf)
{
    ASSERT_EQ(_a31.IndexOf(0, 1, 2), 5);

    uint idx = 0;
    for (uint f = 0; f < _a61.Size(5); f++)
        for (uint e = 0; e < _a61.Size(4); e++)
            for (uint d = 0; d < _a61.Size(3); d++)
                for (uint c = 0; c < _a61.Size(2); c++)
                    for (uint b = 0; b < _a61.Size(1); b++)
                        for (uint a = 0; a < _a61.Size(0); a++)
                            ASSERT_EQ(_a61.IndexOf(a, b, c, d, e, f), idx++);

    ASSERT_EQ(_a31.IndexOf(0, 1, 2, 0, 0, 0), 5);
}
TEST_F(_Array, Iteration)
{
    uint idx = 0;
    for (auto v : _a61)
        ASSERT_EQ(v, _a61(idx++));
}
TEST_F(_Array, Reshaping)
{
    constexpr Array<uint, 3, 2, 1> a1   = _u61;
    constexpr Array<uint, 1, 2, 3> a2   = a1.Reshape<1, 2, 3>();
    constexpr Array<uint, 6> a3         = a1.Flatten();

    for (uint a = 0; a < a1.Count(); a++)
    {
        ASSERT_EQ(a2(a), a1(a));
        ASSERT_EQ(a3(a), a1(a));
    }

    Array<double, 27> a32 = _a32.Flatten();
    for (uint a = 0; a < _a32.Count(); a++)
        ASSERT_EQ(a32(a), _a32(a));
}
TEST_F(_Array, Sizes)
{
    for (uint a = 0; a < _a31.Rank(); a++)
        ASSERT_EQ(_a31.Size(a), a + 1);

    auto size = _a61.Size();
    ASSERT_EQ(size.Count(), 6);
    for (uint a = 0; a < size.Count(); a++)
        ASSERT_EQ(size(a), a + 5);
}
TEST_F(_Array, SubscriptsOf)
{
    constexpr Array<uint, 3> a2 = Array<uint, 1, 2, 3>::SubscriptsOf(5);
    for (uint a = 0; a < 3; a++)
        ASSERT_EQ(a2(a), a);

    uint idx = 0;
    for (uint f = 0; f < _a61.Size(5); f++)
        for (uint e = 0; e < _a61.Size(4); e++)
            for (uint d = 0; d < _a61.Size(3); d++)
                for (uint c = 0; c < _a61.Size(2); c++)
                    for (uint b = 0; b < _a61.Size(1); b++)
                        for (uint a = 0; a < _a61.Size(0); a++)
                            ASSERT_EQ(_a61.SubscriptsOf(idx++), (Array<uint, 6>{ a, b, c, d, e, f }));
}