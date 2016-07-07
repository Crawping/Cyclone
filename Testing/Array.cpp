/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#include <gtest/gtest.h>
#include "Array.h"



class _Array : public ::testing::Test
{
    protected:

        Array<int>      _a0;    
        Array<long>     _a1;
        Array<char>     _a2;
        Array<double>   _a3;

        _Array() :
            _a0(0),
            _a1(1),
            _a2(10),
            _a3(100)
        {
            _a2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
        }
};



TEST_F(_Array, ObjectConstruction)
{
    ASSERT_EQ(_a0.Count(), 0);
    ASSERT_EQ(_a1.Count(), 1);
    ASSERT_EQ(_a2.Count(), 10);
    ASSERT_EQ(_a3.Count(), 100);
}

TEST_F(_Array, ObjectCopying)
{
    Array<char> copy(_a2);
    ASSERT_EQ(_a2.Count(), copy.Count());

    for (uint a = 0; a < _a2.Count(); a++)
        ASSERT_EQ(_a2(a), copy(a));

    copy(8) = '6';
    ASSERT_NE(_a2(8), copy(8));
}

TEST_F(_Array, EqualityOperators)
{
    Array<char> _a2Copy = _a2;

    ASSERT_EQ(_a2, _a2);
    ASSERT_EQ(_a2, _a2Copy);

    _a2Copy(6) = 'q';
    ASSERT_NE(_a2, _a2Copy);
}

TEST_F(_Array, IndexingOperator)
{
    ASSERT_EQ(_a2(0), 'a');
    ASSERT_EQ(_a2(5), 'f');
    ASSERT_EQ(_a2(9), 'j');

    _a2(9) = 'x';
    ASSERT_EQ(_a2(9), 'x');
}