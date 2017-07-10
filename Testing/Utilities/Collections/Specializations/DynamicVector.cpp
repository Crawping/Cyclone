/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#include "Collections/Array.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class DynamicVectorTest : public testing::Test
{
    protected:

        Vector<uint, 4>     _sv0;
        Vector<char, 5>     _sv1;
        Vector<char, 5>     _sv2;
        Vector<char, 10>    _sv3;

        Vector<uint>        _v0;
        Vector<char>        _v1;
        Vector<char>        _v2;

        DynamicVectorTest():
            _sv1{ 'a', 'b', 'c', 'd', 'e' },
            _v1{ 'a', 'b', 'c', 'd', 'e' }
        {
            _v2 = { 'f', 'g', 'h', 'i', 'j' };
        }
};



/** CONSTRUCTION TESTS **/
TEST_F(DynamicVectorTest, Clear)
{
    _v1.Clear();
    ASSERT_EQ(_v1.Count(), 0);
}
TEST_F(DynamicVectorTest, Construction)
{
    ASSERT_EQ(_sv0.Count(), 4);
    ASSERT_EQ(_sv0.Rank(),  1);
    ASSERT_EQ(_v0.Count(),  0);

    ASSERT_EQ(_v1.Count(),  5);
    ASSERT_EQ(_v1.First(),  'a');
    ASSERT_EQ(_v1.Last(),   'e');

    ASSERT_EQ(_v2.Count(),  5);
    ASSERT_EQ(_v2.First(),  'f');
    ASSERT_EQ(_v2.Last(),   'j');
}
TEST_F(DynamicVectorTest, Concatenate)
{
    _v0.Concatenate(256);
    ASSERT_EQ(_v0.Count(), 1);
    ASSERT_EQ(_v0.First(), 256);

    _v1.Concatenate('x');
    ASSERT_EQ(_v1.Count(),    6);
    ASSERT_EQ(_v1.Last(),   'x');
    ASSERT_EQ(_v1(5),       'x');

    _v1.Concatenate(_v2);
    ASSERT_EQ(_v1.Count(), _v2.Count() + 6);
    for (uint a = 6; a < _v1.Count(); a++)
        ASSERT_EQ(_v1(a), _v2(a - 6));

    // Test concatenating an empty vector
    Vector<char> empty;
    _v1.Concatenate(empty);
    ASSERT_EQ(_v1.Count(), _v2.Count() + 6);

    // Test concatenating to an empty vector
    empty.Concatenate(_v2);
    for (uint a = 0; a < _v2.Count(); a++)
        ASSERT_EQ(_v2(a), empty(a));
}
TEST_F(DynamicVectorTest, Fill)
{
    _v1.Fill('y');
    ASSERT_EQ(_v1.Count(), 5);
    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_v1(a), 'y');
}



/** OPERATORS **/
TEST_F(DynamicVectorTest, Indexing)
{
    ASSERT_EQ(_v1(0), 'a');
    ASSERT_EQ(_v1(1), 'b');
    ASSERT_EQ(_v1(2), 'c');
    ASSERT_EQ(_v1(3), 'd');
    ASSERT_EQ(_v1(4), 'e');

    uint idx = 0;
    for (const char& it : _v1)
        ASSERT_EQ(it, _v1(idx++));

    idx = 0;
    for (auto it : _v2)
        ASSERT_EQ(it, _v2(idx++));
}
