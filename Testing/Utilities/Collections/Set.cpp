/* CHANGELOG
 * Written by Josh Grooms on 20161221
 */



#include "Collections/Set.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;


struct CanonicalSets
{
    Vector<int> UnsortedIntegers;
    Vector<int> SortedIntegers;


    CanonicalSets() :
        UnsortedIntegers({ 15, 52, 56, 31, 60, 98, 54, 4, 81, 57, 50, 30, 28, 19, 65, 33, 73, 42 }),
        SortedIntegers({ 4, 15, 19, 28, 30, 31, 33, 42, 50, 52, 54, 56, 57, 60, 65, 73, 81, 98 })
    {

    }

};


class _Set : public testing::Test 
{
    protected:

        CanonicalSets Canon;

        Set<int>    _s0;
        Set<int>    _s1;

        _Set() : 
            _s1(Canon.UnsortedIntegers)
        {

        }

};




/** CONSTRUCTION TESTS **/
TEST_F(_Set, DefaultConstruction)
{
    ASSERT_EQ(_s0.Count(), 0);
    ASSERT_EQ(_s0.Order(), SortOrders::Ascending);
}
TEST_F(_Set, InitializedConstruction)
{
    ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count());
    for (uint a = 0; a < _s1.Count(); a++)
        ASSERT_EQ(_s1(a), Canon.SortedIntegers(a));
}



/** UTILITY TESTS **/
TEST_F(_Set, SortingOrders)
{
    ASSERT_EQ(_s1.Order(), SortOrders::Ascending);
    for (uint a = 0; a < _s1.Count(); a++)
        ASSERT_EQ(_s1(a), Canon.SortedIntegers(a));

    _s1.Order(SortOrders::Descending);
    for (uint a = 0; a < _s1.Count(); a++)
        ASSERT_EQ(_s1(a), Canon.SortedIntegers(_s1.Count() - a - 1));
}
TEST_F(_Set, ValueInsertion)
{
    _s1.Insert(-1);
    ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count() + 1);
    ASSERT_EQ(_s1.First(), -1);

    _s1.Insert(100);
    ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count() + 2);
    ASSERT_EQ(_s1.Last(), 100);

    int idx = _s1.Find(50);
    ASSERT_TRUE(idx > -1);

    // Assert element uniqueness
    for (uint a = 0; a < 2; a++)
    {
        _s1.Insert(51);
        ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count() + 3);
        ASSERT_EQ(_s1(idx + 1), 51);
    }
}
TEST_F(_Set, ValueRemoval)
{
    ASSERT_TRUE(_s1.Contains(52));

    _s1.Remove(52);
    ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count() - 1);
    ASSERT_FALSE(_s1.Contains(52));

    ASSERT_FALSE(_s1.Contains(51));
    _s1.Remove(51);
    ASSERT_EQ(_s1.Count(), Canon.SortedIntegers.Count() - 1);
}