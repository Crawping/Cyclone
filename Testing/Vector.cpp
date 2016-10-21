/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#include "Collections/Vector.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;


struct VectorElement
{
    int Value;
};

class _Vector : public testing::Test
{
    protected:
        
        Vector<uint> _v0;
        Vector<char> _v1;
        Vector<char> _v2;

        Vector<VectorElement*, 4> _v3;


        _Vector() :
            _v1({ 'a', 'b', 'c', 'd', 'e' }),
            _v3({ nullptr, nullptr, nullptr, nullptr })
        {
            _v2 = { 'f', 'g', 'h', 'i', 'j' };
            _v3(0) = new VectorElement{ 1 };
            _v3(1) = new VectorElement{ 2 };
            _v3(2) = new VectorElement{ 3 };
            _v3(3) = new VectorElement{ 4 };
        }
};




/** CONSTRUCTION TESTS **/
TEST_F(_Vector, DefaultConstruction)
{
    ASSERT_EQ(_v0.Count(), 0);
}

TEST_F(_Vector, InitializerListConstruction)
{
    ASSERT_EQ(_v1.Count(), 5);
    ASSERT_EQ(_v1.First(), 'a');
    ASSERT_EQ(_v1.Last(), 'e');
}

TEST_F(_Vector, AssignmentConstruction)
{
    ASSERT_EQ(_v2.Count(), 5);
    ASSERT_EQ(_v2.First(), 'f');
    ASSERT_EQ(_v2.Last(), 'j');
}



/** MANIPULATION TESTS **/
TEST_F(_Vector, VectorClearing)
{
    _v1.Clear();
    ASSERT_EQ(_v1.Count(), 0);
}
TEST_F(_Vector, ElementAppending)
{
    _v0.Append(256);
    ASSERT_EQ(_v0.Count(), 1);
    ASSERT_EQ(_v0.First(), 256);

    _v1.Append('x');
    ASSERT_EQ(_v1.Count(),    6);
    ASSERT_EQ(_v1.Last(),   'x');
    ASSERT_EQ(_v1(5),       'x');
}
TEST_F(_Vector, VectorAppending)
{
    Vector<char> _v1Copy = _v1;

    _v1Copy.Append(_v2);
    ASSERT_EQ(_v1Copy.Count(), _v1.Count() + _v2.Count());

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_v1Copy(a), _v1(a));

    for (uint a = _v1.Count(); a < _v1Copy.Count(); a++)
        ASSERT_EQ(_v1Copy(a), _v2(a - _v1.Count()));

    // Test appending an empty vector
    Vector<char> empty;
    Vector<char> _v2Copy = _v2;
    
    _v2Copy.Append(empty);
    ASSERT_EQ(_v2, _v2Copy);

    // Test appending to an empty vector
    empty.Append(_v2);
    ASSERT_EQ(_v2, empty);
}
TEST_F(_Vector, VectorFilling)
{
    Vector<char> _v1Copy(_v1);
    _v1Copy.Fill('y');
    ASSERT_EQ(_v1.Count(), _v1Copy.Count());

    for (uint a = 0; a < _v1Copy.Count(); a++)
        ASSERT_EQ(_v1Copy(a), 'y');
}



/** OPERATORS **/
TEST_F(_Vector, EqualityOperator)
{
    Vector<char> _v1Copy = _v1;
    ASSERT_EQ(_v1, _v1Copy);
}
TEST_F(_Vector, IndexingOperator)
{
    ASSERT_EQ(_v1(0), 'a');
    ASSERT_EQ(_v1(1), 'b');
    ASSERT_EQ(_v1(2), 'c');
    ASSERT_EQ(_v1(3), 'd');
    ASSERT_EQ(_v1(4), 'e');
}
TEST_F(_Vector, InequalityOperator)
{
    ASSERT_NE(_v1, _v2);
}
TEST_F(_Vector, RangedForLoop)
{
    uint idx = 0;
    for (const char& it : _v1)
        ASSERT_EQ(it, _v1(idx++));

    idx = 0;
    for (auto it : _v2)
        ASSERT_EQ(it, _v2(idx++));
}
TEST_F(_Vector, ElementDeletion)
{
    for (uint a = 0; a < _v3.Count(); a++)
        if (_v3(a)) 
            delete _v3(a);
}