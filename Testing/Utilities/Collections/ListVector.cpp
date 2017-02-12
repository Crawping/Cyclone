/* CHANGELOG 
 * Written by Josh Grooms on 20170110
 */

#include "Collections/ListVector.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _ListVector : public testing::Test
{
    protected:
        
        Vector<int>         _v1 = { 0, 1, 2, 3, 4, 5 };
        Vector<int>         _v2;

        ListVector<int>     _l0;
        ListVector<int>     _l1;


        _ListVector() : 
            _v2(512)
        {
            _v2.Fill(9);
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_ListVector, DefaultConstruction)
{
    ASSERT_EQ(_l0.Count(), 0);
    ASSERT_EQ(_l0.Capacity(), 128);
}




/** UTILITY TESTS **/
TEST_F(_ListVector, CollectionAppending)
{
    _l1.Append(_v1);
    ASSERT_EQ(_l1.Count(), _v1.Count());
    ASSERT_EQ(_l1.Capacity(), 128);

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a));

    _l1.Append(_v2);
    ASSERT_EQ(_l1.Count(), _v1.Count() + _v2.Count());
    ASSERT_EQ(_l1.Capacity(), nextpow2(_v1.Count() + _v2.Count()));

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a));
    for (uint a = _v1.Count(); a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v2(a - _v1.Count()));
}
TEST_F(_ListVector, CollectionInsertion)
{
    _l1.Append(_v2);
    _l1.Insert(256, _v1);
    ASSERT_EQ(_l1.Count(), _v1.Count() + _v2.Count());
    ASSERT_EQ(_l1.Capacity(), nextpow2(_v1.Count() + _v2.Count()));

    for (uint a = 0; a < 256; a++)
        ASSERT_EQ(_l1(a), _v2(a));
    for (uint a = 256; a < 256 + _v1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a - 256));
    for (uint a = 256 + _v1.Count(); a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v2(a - _v1.Count()));
}
TEST_F(_ListVector, CollectionPrepending)
{
    _l1.Prepend(_v1);
    ASSERT_EQ(_l1.Count(), _v1.Count());
    ASSERT_EQ(_l1.Capacity(), 128);

    for (uint a = 0; a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a));

    _l1.Prepend(_v2);
    ASSERT_EQ(_l1.Count(), _v1.Count() + _v2.Count());
    ASSERT_EQ(_l1.Capacity(), nextpow2(_v1.Count() + _v2.Count()));

    for (uint a = 0; a < _v2.Count(); a++)
        ASSERT_EQ(_l1(a), _v2(a));
    for (uint a = _v2.Count(); a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a - _v2.Count()));
}
TEST_F(_ListVector, ElementInsertion)
{
    _l1.Insert(0, 0);
    ASSERT_EQ(_l1(0), 0);
    ASSERT_EQ(_l1.Count(), 1);

    _l1.Insert(1, 20);
    ASSERT_EQ(_l1(1), 20);
    ASSERT_EQ(_l1.Count(), 2);
    ASSERT_EQ(_l1.Capacity(), 128);

    _l1.Insert(1, 10);
    ASSERT_EQ(_l1(0), 0);
    ASSERT_EQ(_l1(1), 10);
    ASSERT_EQ(_l1(2), 20);
    ASSERT_EQ(_l1.Count(), 3);
    ASSERT_EQ(_l1.Capacity(), 128);

    _l1.Insert(0, 30);
    ASSERT_EQ(_l1(0), 30);
    ASSERT_EQ(_l1(1), 0);
    ASSERT_EQ(_l1(2), 10);
    ASSERT_EQ(_l1(3), 20);
    ASSERT_EQ(_l1.Count(), 4);
    ASSERT_EQ(_l1.Capacity(), 128);
}
TEST_F(_ListVector, ElementRemoval)
{
    _l1.Append(_v1);
    _l1.Remove(0);
    ASSERT_EQ(_l1.Count(), _v1.Count() - 1);
    ASSERT_EQ(_l1.First(), _v1(1));

    _l1.Remove(_l1.Count() - 1);
    ASSERT_EQ(_l1.Count(), _v1.Count() - 2);
    ASSERT_EQ(_l1.Last(), _v1(_v1.Count() - 2));

    _l1.Remove(2);
    ASSERT_EQ(_l1.Count(), _v1.Count() - 3);
    ASSERT_EQ(_l1(2), _v1(4));
}