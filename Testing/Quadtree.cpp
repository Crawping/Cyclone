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

        Vector<int, 8> _v1;



        _Quadtree() : 
            _a1(  0,   0,  8,   8),
            _a2(  0,   0,  4,   4),
            _a3(-16, -16, 32,  32),
            _a4(  0,   4,  2,   2),
            _v1({ 16, 32, 64, 128, 256, 512, 1024, 2048 })
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



///** UTILITY TESTS **/
TEST_F(_Quadtree, SubtreeInsertion)
{
    _q1.Insert(_a1, _v1(0));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 1);

    _q1.Insert(_a2, _v1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);

    List<int> treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 2);

    for (uint a = 0; a < treeContents.Count(); a++)
        ASSERT_EQ(treeContents(a), _v1(a));

    _q1.Insert(_a4, _v1(2));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 3);

    treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 3);

    for (uint a = 0; a < treeContents.Count(); a++)
        ASSERT_EQ(treeContents(a), _v1(a));

}

TEST_F(_Quadtree, SupertreeInsertion)
{
    _q1.Insert(_a2, _v1(2));
    ASSERT_EQ(_q1.Bounds(), _a2);
    ASSERT_EQ(_q1.Count(), 1);

    _q1.Insert(_a1, _v1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);

    List<int> treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 2);

    for (uint a = 0; a < treeContents.Count(); a++)
        ASSERT_EQ(treeContents(a), _v1(a + 1));

    _q1.Insert(_a3, _v1(0));
    ASSERT_EQ(_q1.Bounds(), _a3);
    ASSERT_EQ(_q1.Count(), 3);

    treeContents = _q1.Index(_a3);
    ASSERT_EQ(treeContents.Count(), 3);

    for (uint a = 0; a < treeContents.Count(); a++)
        ASSERT_EQ(treeContents(a), _v1(a));
}

TEST_F(_Quadtree, ComplexInsertions)
{
    Area smallUL(0.25f, 0.60f, 0.12f, 0.30f);
    Area largeUL(0.01f, 0.51f, 0.48f, 0.48f);
    
    Area smallUR(0.66f, 0.66f, 0.33f, 0.33f);
    Area largeUR(0.51f, 0.51f, 0.48f, 0.48f);
    
    Area smallLL(0.33f, 0.25f, 0.11f, 0.24f);
    Area largeLL(0.01f, 0.01f, 0.48f, 0.48f);

    Area smallLR(0.75f, 0.33f, 0.08f, 0.01f);
    Area largeLR(0.51f, 0.01f, 0.48f, 0.48f);

    smallUL.Scale(10).Translate(-5);
    smallUR.Scale(10).Translate(-5);
    smallLL.Scale(10).Translate(-5);
    smallLR.Scale(10).Translate(-5);

    largeUL.Scale(10).Translate(-5);
    largeUR.Scale(10).Translate(-5);
    largeLL.Scale(10).Translate(-5);
    largeLR.Scale(10).Translate(-5);

    _q1.Insert(smallUL, _v1(0));
    _q1.Insert(largeUL, _v1(1));
    _q1.Insert(smallUR, _v1(2));
    _q1.Insert(largeUR, _v1(3));

    _q1.Insert(smallLL, _v1(4));
    _q1.Insert(largeLL, _v1(5));
    _q1.Insert(smallLR, _v1(6));
    _q1.Insert(largeLR, _v1(7));

    ASSERT_EQ(_q1.Count(), 8);

    Area total(smallUL);
    total
        .Union(largeUL)
        .Union(smallUR)
        .Union(largeUR)
        .Union(smallLL)
        .Union(largeLL)
        .Union(smallLR)
        .Union(largeLR);

    ASSERT_EQ(_q1.Bounds(), total) << "Q1: " << _q1.Bounds().Report() << "\n" <<
        "Total: " << total.Report() << "\n";
}



