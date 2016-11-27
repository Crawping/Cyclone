/* CHANGELOG 
 * Written by Josh Grooms on 20161126
 */

#include "Collections/BST.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _BST : public testing::Test
{
    protected:
        
        BST<int, int>       _b0;
        BST<int, int>       _b1;
        BST<int, int>       _b2;


        _BST() 
        {
            _b2.Insert(2, 20);
            _b2.Insert(1, 10);
            _b2.Insert(4, 40);
            _b2.Insert(3, 30);
            _b2.Insert(5, 50);
            _b2.Insert(0,  0);
        }
};




/** CONSTRUCTION TESTS **/
TEST_F(_BST, DefaultConstruction)
{
    ASSERT_EQ(_b0.Count(), 0);
}




/** UTILITY TESTS **/
TEST_F(_BST, NodeInsertion)
{
    _b1.Insert(50, 500);
    _b1.Insert(20, 200);
    _b1.Insert(40, 400);
    _b1.Insert(10, 100);
    _b1.Insert(30, 300);

    ASSERT_EQ(_b1.Count(), 5);

    auto keys = _b1.Keys();
    auto values = _b1.Values();

    ASSERT_EQ(keys.Count(), 5);
    ASSERT_EQ(values.Count(), 5);

    for (uint a = 0; a < keys.Count(); a++)
    {
        ASSERT_EQ(keys(a),      (a + 1) * 10);
        ASSERT_EQ(values(a),    (a + 1) * 100);
    }
}
TEST_F(_BST, IndexResolution)
{
    for (uint a = 0; a < _b2.Count(); a++)
        ASSERT_EQ(_b2.IndexOf(a), a);
}



/** OPERATOR TESTS **/
TEST_F(_BST, KeyIndexing)
{
    for (uint a = 0; a < 6; a++)
        ASSERT_EQ(_b2[a], a * 10);
}
TEST_F(_BST, NumericIndexing)
{
    for (uint a = 0; a < 5; a++)
        ASSERT_EQ(_b2(a), a * 10);
}

