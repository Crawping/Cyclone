/* CHANGELOG
* Written by Josh Grooms on 20170702
*/

#include "Graphs/Node.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class NodeTest: public testing::Test
{
    protected:

        Node<int, 5, 5, 5>  _n0;


        NodeTest()
        {

        }
};



TEST_F(NodeTest, Construction)
{
    ASSERT_EQ(_n0.Degree,   125);
    ASSERT_EQ(_n0.Rank,     3);
}
TEST_F(NodeTest, Indexing)
{
    _n0(4, 4, 4) = new Node<int, 5, 5, 5>(32);

    for (uint a = 0; a < _n0.Degree - 1; a++)
        ASSERT_EQ(_n0(a),   nullptr);

    ASSERT_NE(_n0(4, 4, 4), nullptr);
    ASSERT_EQ(_n0(4, 4, 4)->Value(), 32);
}
