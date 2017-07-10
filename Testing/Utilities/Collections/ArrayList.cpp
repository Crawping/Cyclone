/* CHANGELOG 
 * Written by Josh Grooms on 20170110
 */

#include "Collections/ArrayList.h"
#include "Math/Vector3.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class ArrayListTest: public testing::Test
{
    protected:
        
        Vector<int>         _v1 = { 0, 1, 2, 3, 4, 5 };
        Vector<int>         _v2;

        ArrayList<int>      _l0;
        ArrayList<int>      _l1;
        ArrayList<ulong>    _l2;
        ArrayList<Vector3>  _l3;

        ArrayListTest() : 
            _v2(512),
            _l1(128),
            _l2(256)
        {
            _v2.Fill(9);
            _l2.Insert(0, 10);

            for (uint a = 0; a < 10; a++)
                _l3.Append(Vector3(a));
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(ArrayListTest, Construction)
{
    ASSERT_EQ(_l0.Count(),      0);
    ASSERT_EQ(_l0.Capacity(),   32);

    ASSERT_EQ(_l1.Count(),      0);
    ASSERT_EQ(_l1.Capacity(),   128);

    ASSERT_EQ(_l2.Count(),      1);
    ASSERT_EQ(_l2.Capacity(),   256);
}




/** UTILITY TESTS **/
TEST_F(ArrayListTest, Append)
{
    uint c1 = _l1.Capacity();
    _l1.Append(_v1);

    ASSERT_EQ(_l1.Count(),      _v1.Count());
    ASSERT_EQ(_l1.Capacity(),   c1);

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a));

    _l1.Append(_v2);
    ASSERT_EQ(_l1.Count(),      _v1.Count() + _v2.Count());
    ASSERT_EQ(_l1.Capacity(),   Math::NextPower2(c1 + _v1.Count() + _v2.Count()));

    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_l1(a),       _v1(a));
    for (uint a = _v1.Count(); a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a),       _v2(a - _v1.Count()));
}
TEST_F(ArrayListTest, Insert)
{    
    uint c1 = _l1.Capacity();

    _l1.Insert(0, 0);
    ASSERT_EQ(_l1(0),           0);
    ASSERT_EQ(_l1.Count(),      1);

    _l1.Insert(1, 20);
    ASSERT_EQ(_l1(1),           20);
    ASSERT_EQ(_l1.Count(),      2);
    ASSERT_EQ(_l1.Capacity(),   c1);

    _l1.Insert(1, 10);
    ASSERT_EQ(_l1(0),           0);
    ASSERT_EQ(_l1(1),           10);
    ASSERT_EQ(_l1(2),           20);
    ASSERT_EQ(_l1.Count(),      3);
    ASSERT_EQ(_l1.Capacity(),   c1);

    _l1.Insert(0, 0, 1, 2, 3, 4, 5);
    ASSERT_EQ(_l1.Count(),      9);
    ASSERT_EQ(_l1.Capacity(),   c1);

    for (uint a = 0; a < 6; a++)
        ASSERT_EQ(_l1(a),       a);

    _l1.Insert(0, _v1, _v1);
    ASSERT_EQ(_l1.Count(),      21);
    ASSERT_EQ(_l1.Capacity(),   c1);

    for (uint a = 0; a < 6; a++)
    {
        ASSERT_EQ(_l1(a),       a);
        ASSERT_EQ(_l1(a + 6),   a);
        ASSERT_EQ(_l1(a + 12),  a);
    }

    _l1.Insert(21, _v1, 6, 7, 8, 9);
    ASSERT_EQ(_l1.Count(),      31);
    ASSERT_EQ(_l1.Capacity(),   c1);

    for (uint a = 0; a < 10; a++)
        ASSERT_EQ(_l1(21 + a),  a);

}
TEST_F(ArrayListTest, Prepend)
{
    uint c1 = _l1.Capacity();
    _l1.Prepend(_v1);

    ASSERT_EQ(_l1.Count(),      _v1.Count());
    ASSERT_EQ(_l1.Capacity(),   c1);

    for (uint a = 0; a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a));

    _l1.Prepend(_v2);
    ASSERT_EQ(_l1.Count(), _v1.Count() + _v2.Count());
    ASSERT_EQ(_l1.Capacity(), Math::NextPower2(_v1.Count() + _v2.Count()));

    for (uint a = 0; a < _v2.Count(); a++)
        ASSERT_EQ(_l1(a), _v2(a));
    for (uint a = _v2.Count(); a < _l1.Count(); a++)
        ASSERT_EQ(_l1(a), _v1(a - _v2.Count()));
}
TEST_F(ArrayListTest, Remove)
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
TEST_F(ArrayListTest, Find)
{
    _l1.Append(_v1);
    ASSERT_EQ(_l1.Find(3),       3);
    ASSERT_EQ(_l1.Find(5),       5);
    ASSERT_EQ(_l1.Find(-10),    -1);
}
TEST_F(ArrayListTest, Gather)
{
    auto lengths = _l3.Gather(Getter<float, const Vector3>(&Vector3::Norm));
    auto x = _l3.Gather(Field<float, Vector3>(&Vector3::X));
    auto y = _l3.Gather(Field<float, Vector3>(&Vector3::Y));

    for (uint a = 0; a < lengths.Count(); a++)
    {
        ASSERT_EQ(lengths(a),   _l3(a).Norm());
        ASSERT_EQ(x(a),         _l3(a).X);
        ASSERT_EQ(y(a),         _l3(a).Y);
    }
}
TEST_F(ArrayListTest, Reallocation)
{
    uint c1 = _l2.Capacity();
    _l2.Insert(c1, 10, 20, 30, 40, 50);

    ASSERT_EQ(_l2.Capacity(),   Math::NextPower2(c1 + 1));

    uint c2 = _l2.Capacity();
    _l2.Insert(c2, Vector<ulong>{ 60, 70, 80, 90, 100 });

    ASSERT_EQ(_l2.Capacity(),   Math::NextPower2(c2 + 1));

    for (uint a = 0; a < 5; a++)
    {
        ASSERT_EQ(_l2(c1 + a),  (a + 1) * 10);
        ASSERT_EQ(_l2(c2 + a),  (a + 6) * 10);
    }
}