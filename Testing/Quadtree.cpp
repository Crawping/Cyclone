/* CHANGELOG
 * Written by Josh Grooms on 20161019
 */

#include "Collections/Quadtree.h"
#include "Collections/Vector.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Quadtree : public testing::Test
{
    protected:
        
        Area _a1;
        Area _a2;
        Area _a3;
        Area _a4;

        Quadtree<int> _q0;
        Quadtree<int> _q1;

        Vector<int, 4> _vi1;



        _Quadtree() : 
            _a1(0, 0, 8, 8),
            _a2(0, 0, 4, 4),
            _a3(4, 4, 3, 3),
            _a4(0, 4, 2, 2),
            _vi1({ 16, 32, 64, 128 })
        {
            
        }
};




/** CONSTRUCTION TESTS **/
TEST_F(_Quadtree, DefaultConstruction)
{
    ASSERT_EQ(_q0.Bounds(), Area::Empty);
    ASSERT_EQ(_q0.Count(), 0);
    ASSERT_TRUE(_q0.IsEmpty());
}



/** UTILITY TESTS **/
TEST_F(_Quadtree, SubtreeInsertion)
{
    _q1.Insert(_a1, _vi1(0));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 1);

    _q1.Insert(_a2, _vi1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);

    List<int> treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 2);

    for (uint a = 0; a < treeContents.Count(); a++)
        ASSERT_EQ(treeContents(a), _vi1(a));
}

TEST_F(_Quadtree, SupertreeInsertion)
{
    _q1.Insert(_a2, _vi1(0));
    ASSERT_EQ(_q1.Bounds(), _a2);
    ASSERT_EQ(_q1.Count(), 1);

    _q1.Insert(_a1, _vi1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);
}



