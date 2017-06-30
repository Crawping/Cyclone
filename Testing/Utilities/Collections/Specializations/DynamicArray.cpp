/* CHANGELOG
 * Written by Josh Grooms on 20170629
 */

#include "Collections/Array.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class DynamicArrayTest: public testing::Test
{
    protected:

        Array<int>      _a0;
        Array<int>      _a1;
        Array<double>   _a2;


        DynamicArrayTest():
            _a1{ 1, 2, 3, 4, 5 },
            _a2(5, 6, 7, 8, 9)
        {
            for (uint a = 0; a < _a2.Count(); a++)
                _a2(a) = _a2.Count() - a;
        }

};



TEST_F(DynamicArrayTest, Construction)
{
    ASSERT_EQ(_a0.Count(),  0);
    ASSERT_EQ(_a0.Rank(),   0);

    ASSERT_EQ(_a1.Count(),  5);
    ASSERT_EQ(_a1.Rank(),   1);

    ASSERT_EQ(_a2.Count(),  Math::Product(5, 6, 7, 8, 9));
    ASSERT_EQ(_a2.Rank(),   5);
}
TEST_F(DynamicArrayTest, Count)
{
    ASSERT_EQ(_a0.Count(0), 0);
    ASSERT_EQ(_a0.Count(1), 0);

    ASSERT_EQ(_a1.Count(0), 5);
    ASSERT_EQ(_a1.Count(1), 5);
    ASSERT_EQ(_a1.Count(2), 5);

    uint count = 1;
    for (uint a = 0; a < _a2.Rank(); a++)
        ASSERT_EQ(_a2.Count(a),     count *= _a2.Size(a));
}
TEST_F(DynamicArrayTest, Indexing)
{
    for (uint a = 0; a < _a1.Count(); a++)
        ASSERT_EQ(_a1(a),   a + 1);

    int idx = 1;
    for (auto a : _a1)
        ASSERT_EQ(a,        idx++);

    idx = _a2.Count();
    for (uint e = 0; e < _a2.Size(4); e++)
        for (uint d = 0; d < _a2.Size(3); d++)
            for (uint c = 0; c < _a2.Size(2); c++)
                for (uint b = 0; b < _a2.Size(1); b++)
                    for (uint a = 0; a < _a2.Size(0); a++)
                        ASSERT_EQ(_a2(a, b, c, d, e), idx--);
}
TEST_F(DynamicArrayTest, Reshape)
{
    auto a2(_a2);
    a2.Reshape(1, _a2.Count());

    ASSERT_EQ(a2.Count(),   _a2.Count());
    ASSERT_EQ(a2.Rank(),    2);
    ASSERT_EQ(a2.Size(0),   1);
    ASSERT_EQ(a2.Size(1),   _a2.Count());

    a2.Reshape(5, 6, 7, 8, 9);
    ASSERT_EQ(a2.Count(),   _a2.Count());
    ASSERT_EQ(a2.Rank(),    _a2.Rank());

    for (uint a = 0; a < a2.Count(); a++)
        ASSERT_DOUBLE_EQ(a2(a), _a2(a));
}
TEST_F(DynamicArrayTest, Size)
{
    ASSERT_EQ(_a0.Size(0),  0);
    ASSERT_EQ(_a0.Size(1),  0);

    ASSERT_EQ(_a1.Size(0),  5);
    ASSERT_EQ(_a1.Size(1),  1);
    ASSERT_EQ(_a1.Size(2),  1);

    for (uint a = 0; a < _a2.Rank(); a++)
        ASSERT_EQ(_a2.Size(a), a + 5);
}