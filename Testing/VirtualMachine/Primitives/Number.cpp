/* CHANGELOG
 * Written by Josh Grooms on 20170429
 */

#include "Primitives/Number.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;



class _Number : public testing::Test
{
    protected:

        Number _i0;

        Number _c1;
        Number _c2;

        Number _f1;
        Number _f2;

        Number _d1;
        Number _d2;



        _Number() :
            _c1(NumericTypes::Character, 'x'),
            _c2('x'),
            _d1(3.14159),
            _d2(-1234.5678),
            _f1(3.14159f),
            _f2(-1234.5678f)
        {

        }
};



/** OPERATORS **/
TEST_F(_Number, Construction)
{
    ASSERT_EQ(_i0.Type(),       NumericTypes::Integer32);
    ASSERT_EQ(_i0.Value(),      0);

    ASSERT_EQ(_c1.Type(),       NumericTypes::Character);
    ASSERT_EQ(_c1.Value(),      'x');

    ASSERT_EQ(_d1.Type(),       NumericTypes::Float64);
    ASSERT_EQ(_d1.Value(),      3.14159);

    ASSERT_EQ(_f1.Type(),       NumericTypes::Float32);
    ASSERT_EQ(_f1.Value(),      3.14159f);
}
TEST_F(_Number, Casting)
{
    Number d1 = _i0.Cast(NumericTypes::Float64);
    ASSERT_EQ(d1.Type(),        NumericTypes::Float64);

    Number i1 = _f1.Cast(NumericTypes::Integer32);
    ASSERT_EQ(i1.Type(),        NumericTypes::Integer32);
}
TEST_F(_Number, EqualityOperators)
{
    ASSERT_EQ(_i0 != _c1,       true);
    ASSERT_EQ(_c1 == _c2,       true);
    ASSERT_EQ(_c2 == _c2,       true);

    ASSERT_EQ(_d1 == _d2,       false);
    ASSERT_EQ(_d1 == _d1,       true);

    ASSERT_FLOAT_EQ(_d1.Value(), _f1.Value());
}
TEST_F(_Number, MathOperators)
{
    Number i1(_i0 + _c1);
    Number c1 = _c1 + _c2;

    ASSERT_EQ(i1.Type(),                NumericTypes::Integer32);
    ASSERT_EQ(i1.Value(),               _i0.Value() + _c1.Value()); 

    ASSERT_EQ(c1.Type(),                NumericTypes::Character);
    ASSERT_EQ(c1.Value(),               _c1.Value() + _c2.Value());
    ASSERT_EQ(c1.Value(),               'x' + 'x');

    ASSERT_EQ((_i0 * _d2).Type(),       NumericTypes::Float64);
    ASSERT_EQ((_i0 * _d2).Value(),      _i0.Value() * _d2.Value());
    ASSERT_EQ((_d1 * _d2).Value(),      _d1.Value() * _d2.Value());

    ASSERT_EQ((-_d1).Value(),           -(_d1.Value()));
    ASSERT_EQ((_d1 / _d2).Value(),      _d1.Value() / _d2.Value());
    ASSERT_EQ((_d1 - _d2).Value(),      _d1.Value() - _d2.Value());
    ASSERT_EQ((_d1 | _d2).Value(),      (ulong)_d1.Value() | (ulong)_d2.Value());
    ASSERT_EQ((_d1 & _d2).Value(),      (ulong)_d1.Value() & (ulong)_d2.Value());
    ASSERT_EQ((_d1 ^ _d2).Value(),      (ulong)_d1.Value() ^ (ulong)_d2.Value());
}