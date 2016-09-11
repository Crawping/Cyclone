/* CHANGELOG
 * Written by Josh Grooms on 20160910
 */

#include "Collections/List.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _List : public testing::Test
{
    protected:

        List<uint> _l0;
        List<char> _l1;
        List<char> _l2;

        _List() : 
            _l1({ 'a', 'b', 'c', 'd', 'e' })
        {
            _l2 = { 'f', 'g', 'h', 'i', 'j' };
        }
        
};



/** CONSTRUCTION TESTS **/
TEST_F(_List, DefaultConstruction)
{
    ASSERT_EQ(_l0.Count(), 0);
}

TEST_F(_List, InitializerListConstruction)
{
    ASSERT_EQ(_l1.Count(), 5);
    ASSERT_EQ(_l1.First(), 'a');
    ASSERT_EQ(_l1.Last(), 'e');
}

TEST_F(_List, AssignmentConstruction)
{
    ASSERT_EQ(_l2.Count(), 5);
    ASSERT_EQ(_l2.First(), 'f');
    ASSERT_EQ(_l2.Last(), 'j');
}



/** MANIPULATION TESTS **/
TEST_F(_List, ListClearing)
{
    _l1.Clear();

    ASSERT_EQ(_l1.Count(), 0);
}
TEST_F(_List, NodeAppending)
{
    _l0.Append(100);

    ASSERT_EQ(_l0.Count(), 1);
    ASSERT_EQ(_l0.First(), 100);
    
    _l1.Append('z');
    ASSERT_EQ(_l1.Count(), 6);
    ASSERT_EQ(_l1.Last(), 'z');
    ASSERT_EQ(_l1(5), 'z');
}
TEST_F(_List, ListAppending)
{
    List<char> _l1Copy = _l1;
    _l1Copy.Append(_l2);
    ASSERT_EQ(_l1Copy.Count(), _l1.Count() + _l2.Count());
    ASSERT_EQ(_l1Copy.First(), 'a');
    ASSERT_EQ(_l1Copy.Last(), 'j');

    for (uint a = 0; a < _l1.Count(); a++)
        ASSERT_EQ(_l1Copy(a), _l1(a));

    for (uint a = _l1.Count(); a < _l1Copy.Count(); a++)
        ASSERT_EQ(_l1Copy(a), _l2(a - _l1.Count()));
}
TEST_F(_List, NodeInsertion)
{
    _l1.Insert(3, 'g');

    ASSERT_EQ(_l1.Count(), 6);
    ASSERT_EQ(_l1(0), 'a');
    ASSERT_EQ(_l1(1), 'b');
    ASSERT_EQ(_l1(2), 'c');
    ASSERT_EQ(_l1(3), 'g');
    ASSERT_EQ(_l1(4), 'd');
    ASSERT_EQ(_l1(5), 'e');
}

TEST_F(_List, NodePrepending)
{
    _l0.Prepend(200);
    ASSERT_EQ(_l0.Count(), 1);
    ASSERT_EQ(_l0.Last(), 200);

    _l1.Prepend('g');
    ASSERT_EQ(_l1.Count(), 6);
    ASSERT_EQ(_l1.First(), 'g');
    ASSERT_EQ(_l1(0), 'g');
}

TEST_F(_List, NodeRemoval)
{
    _l1.Remove(2);

    ASSERT_EQ(_l1.Count(), 4);
    ASSERT_EQ(_l1.First(), 'a');
    ASSERT_EQ(_l1.Last(), 'e');

    ASSERT_EQ(_l1(0), 'a');
    ASSERT_EQ(_l1(1), 'b');
    ASSERT_EQ(_l1(2), 'd');
    ASSERT_EQ(_l1(3), 'e');
}

TEST_F(_List, IndexingOperator)
{
    _l0.Append(64);
    ASSERT_EQ(_l0(0), 64);

    ASSERT_EQ(_l1(0), 'a');
    ASSERT_EQ(_l1(1), 'b');
    ASSERT_EQ(_l1(2), 'c');
    ASSERT_EQ(_l1(3), 'd');
    ASSERT_EQ(_l1(4), 'e');
}