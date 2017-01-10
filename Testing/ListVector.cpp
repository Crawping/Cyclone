/* CHANGELOG 
 * Written by Josh Grooms on 20170110
 */

#include "Collections/ListVector.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _ListVector : public testing::Test
{
    protected:

        ListVector<int>     _l0;
        ListVector<int>     _l1;


        _ListVector()
        {

        }

};



TEST_F(_ListVector, DefaultConstruction)
{
    ASSERT_EQ(_l0.Count(), 0);
    ASSERT_EQ(_l0.Capacity(), 128);
}

TEST_F(_ListVector, ElementInsertion)
{
    _l1.Insert(10, 10);
    ASSERT_EQ(_l1(10), 10);
    ASSERT_EQ(_l1.Count(), 11);

    _l1.Insert(128, 128);
    ASSERT_EQ(_l1(128), 128);
    ASSERT_EQ(_l1.Count(), 129);
    ASSERT_EQ(_l1.Capacity(), 256);

    _l1.Insert(10, 11);
    ASSERT_EQ(_l1(10), 11);
    ASSERT_EQ(_l1(11), 10);
    ASSERT_EQ(_l1(129), 128);
    ASSERT_EQ(_l1.Count(), 130);
    ASSERT_EQ(_l1.Capacity(), 256);
}