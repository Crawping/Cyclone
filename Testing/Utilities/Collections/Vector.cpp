/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#include "Collections/Vector.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Vector : public testing::Test
{
    protected:

        Vector<uint, 4>     _sv0;
        Vector<char, 5>     _sv1;
        Vector<char, 5>     _sv2;
        Vector<char, 10>    _sv3;

        Vector<uint>        _v0;
        Vector<char>        _v1;
        Vector<char>        _v2;

        _Vector():
            _sv1({ 'a', 'b', 'c', 'd', 'e' }),
            _v1({ 'a', 'b', 'c', 'd', 'e' })
        {
            _v2 = { 'f', 'g', 'h', 'i', 'j' };
            _sv2 = Vector<char, 5>(_v2, 0, _v2.Count());
            _sv3 = Vector<char, 10>(_v1, 0, _v1.Count());

            _sv3.Set(5, _v2, 0, _v2.Count());
        }
};



/** CONSTRUCTION TESTS **/
TEST_F(_Vector, DefaultConstruction)
{
    ASSERT_EQ(_sv0.Count(), 4);
    ASSERT_EQ(_sv0.Rank(),  1);
    ASSERT_EQ(_v0.Count(),  0);
}
TEST_F(_Vector, InitializerListConstruction)
{
    ASSERT_EQ(_v1.Count(),  5);
    ASSERT_EQ(_v1.First(),  'a');
    ASSERT_EQ(_v1.Last(),   'e');
}
TEST_F(_Vector, AssignmentConstruction)
{
    for (uint a = 0; a < _sv2.Count(); a++)
        ASSERT_EQ(_sv2(a),  _v2(a));

    ASSERT_EQ(_v2.Count(),  5);
    ASSERT_EQ(_v2.First(),  'f');
    ASSERT_EQ(_v2.Last(),   'j');
}



/** MANIPULATION TESTS **/
TEST_F(_Vector, Clearing)
{
    _v1.Clear();
    ASSERT_EQ(_v1.Count(), 0);
}
TEST_F(_Vector, ElementConcatenation)
{
    _v0.Concatenate(256);
    ASSERT_EQ(_v0.Count(), 1);
    ASSERT_EQ(_v0.First(), 256);

    _v1.Concatenate('x');
    ASSERT_EQ(_v1.Count(),    6);
    ASSERT_EQ(_v1.Last(),   'x');
    ASSERT_EQ(_v1(5),       'x');
}
TEST_F(_Vector, Slicing)
{
    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_sv3(a), _v1(a));

    for (uint a = 0; a < _v2.Count(); a++)
        ASSERT_EQ(_sv3(a + _v1.Count()), _v2(a));
}
TEST_F(_Vector, VectorConcatenation)
{
    Vector<char> _v1Copy = _v1;

    _v1Copy.Concatenate(_v2);
    ASSERT_EQ(_v1Copy.Count(), _v1.Count() + _v2.Count());

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_v1Copy(a), _v1(a));

    for (uint a = _v1.Count(); a < _v1Copy.Count(); a++)
        ASSERT_EQ(_v1Copy(a), _v2(a - _v1.Count()));

    // Test concatenating an empty vector
    Vector<char> empty;
    Vector<char> _v2Copy = _v2;
    
    // Test concatenating to an empty vector
    empty.Concatenate(_v2);
    for (uint a = 0; a < _v2.Count(); a++)
        ASSERT_EQ(_v2(a), empty(a));
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
TEST_F(_Vector, IndexingOperator)
{
    ASSERT_EQ(_v1(0), 'a');
    ASSERT_EQ(_v1(1), 'b');
    ASSERT_EQ(_v1(2), 'c');
    ASSERT_EQ(_v1(3), 'd');
    ASSERT_EQ(_v1(4), 'e');
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