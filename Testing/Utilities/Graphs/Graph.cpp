/* CHANGELOG
 * Written by Josh Grooms on 20170702
 */

#include "Graphs/Graph.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class GraphTest: public testing::Test
{
    protected:
        
        Graph<int, 5, 5, 5>     _g0;

        GraphTest()
        {

        }

};



TEST_F(GraphTest, Construction)
{
    ASSERT_EQ(_g0.Degree,   125);
    ASSERT_EQ(_g0.Rank,     3);
}
TEST_F(GraphTest, Indexing)
{
    for (uint a = 0; a < _g0.Degree; a++)
        ASSERT_EQ(_g0(a),   nullptr);
}
TEST_F(GraphTest, Set)
{
    _g0.Set({ 4, 4, 4 }, 64);
    ASSERT_EQ(_g0(3, 3, 3), nullptr);
    ASSERT_NE(_g0(4, 4, 4), nullptr);
}