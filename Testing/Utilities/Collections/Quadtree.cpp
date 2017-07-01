/* CHANGELOG
 * Written by Josh Grooms on 20161019
 */

#include "Collections/Quadtree.h"
#include "Collections/Array.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Quadtree : public testing::Test
{
    protected:
        
        Area _a1;
        Area _a2;
        Area _a3;
        Area _a4;

        Area SmallNW;
        Area LargeNW;

        Area SmallNE;
        Area LargeNE;

        Area SmallSW;
        Area LargeSW;

        Area SmallSE;
        Area LargeSE;



        Quadtree<int> _q0;
        Quadtree<int> _q1;
        Quadtree<int> _q2;

        Vector<int, 8> _v1;




        _Quadtree() : 
            _a1(  0,   0,  8,   8),
            _a2(  0,   0,  4,   4),
            _a3(-16, -16, 32,  32),
            _a4(  0,   4,  2,   2),

            SmallNW(0.25f, 0.60f, 0.12f, 0.30f),
            LargeNW(0.01f, 0.51f, 0.48f, 0.48f),

            SmallNE(0.66f, 0.66f, 0.33f, 0.33f),
            LargeNE(0.51f, 0.51f, 0.48f, 0.48f),

            SmallSW(0.33f, 0.25f, 0.11f, 0.20f),
            LargeSW(0.01f, 0.01f, 0.48f, 0.48f),

            SmallSE(0.75f, 0.33f, 0.08f, 0.01f),
            LargeSE(0.51f, 0.01f, 0.48f, 0.48f),

            _v1({ 16, 32, 64, 128, 256, 512, 1024, 2048 })
        {
            _q2.Insert(SmallNW, _v1(0));
            _q2.Insert(LargeNW, _v1(1));
            _q2.Insert(SmallNE, _v1(2));
            _q2.Insert(LargeNE, _v1(3));
            //  
            _q2.Insert(SmallSW, _v1(4));
            _q2.Insert(LargeSW, _v1(5));
            _q2.Insert(SmallSE, _v1(6));
            _q2.Insert(LargeSE, _v1(7));
        }
};




/** CONSTRUCTION TESTS **/
TEST_F(_Quadtree, DefaultConstruction)
{
    ASSERT_EQ(_q0.Bounds(), Area::Empty);
    ASSERT_EQ(_q0.Count(), 0);
    ASSERT_TRUE(_q0.IsEmpty());
}



/** PROPERTY TESTS **/
TEST_F(_Quadtree, KeysGetAccessor)
{
    List<Area> keys = _q2.Keys();
    ASSERT_EQ(keys.Count(), _q2.Count());

    //Vector<Area, 8> expKeys = { LargeNE, SmallNE, LargeNW, SmallNW, LargeSW, SmallSW, LargeSE, SmallSE };
    //uint idx = 0;
    //for (Area k : keys)
    //    ASSERT_EQ(k, expKeys(idx++));
}



/** UTILITY TESTS **/
TEST_F(_Quadtree, SubtreeInsertion)
{
    _q1.Insert(_a1, _v1(0));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 1);

    // Insert a bounding area smaller than the first
    _q1.Insert(_a2, _v1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);

    List<int> treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 2);

    uint idx = 0;
    for (int element : treeContents)
        ASSERT_EQ(element, _v1(idx++));

    // Insert another smaller bounding area
    _q1.Insert(_a4, _v1(2));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 3);

    treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 3);

    idx = 0;
    for (int element : treeContents)
        ASSERT_EQ(element, _v1(idx++));

}

TEST_F(_Quadtree, SupertreeInsertion)
{
    _q1.Insert(_a2, _v1(2));
    ASSERT_EQ(_q1.Bounds(), _a2);
    ASSERT_EQ(_q1.Count(), 1);

    // Insert a bounding area larger than the first
    _q1.Insert(_a1, _v1(1));
    ASSERT_EQ(_q1.Bounds(), _a1);
    ASSERT_EQ(_q1.Count(), 2);

    List<int> treeContents = _q1.Index(_a1);
    ASSERT_EQ(treeContents.Count(), 2);

    uint idx = 1;
    for (int element : treeContents)
        ASSERT_EQ(element, _v1(idx++));

    // Insert another larger bounding area
    _q1.Insert(_a3, _v1(0));
    ASSERT_EQ(_q1.Bounds(), _a3);
    ASSERT_EQ(_q1.Count(), 3);

    treeContents = _q1.Index(_a3);
    ASSERT_EQ(treeContents.Count(), 3);

    idx = 0;
    for (int element : treeContents)
        ASSERT_EQ(element, _v1(idx++));
}

TEST_F(_Quadtree, ComplexInsertions)
{
    SmallNW.Scale(10).Translate(-5);
    SmallNE.Scale(10).Translate(-5);
    SmallSW.Scale(10).Translate(-5);
    SmallSE.Scale(10).Translate(-5);

    LargeNW.Scale(10).Translate(-5);
    LargeNE.Scale(10).Translate(-5);
    LargeSW.Scale(10).Translate(-5);
    LargeSE.Scale(10).Translate(-5);

    _q1.Insert(SmallNW, _v1(0));
    _q1.Insert(LargeNW, _v1(1));
    _q1.Insert(SmallNE, _v1(2));
    _q1.Insert(LargeNE, _v1(3));

    _q1.Insert(SmallSW, _v1(4));
    _q1.Insert(LargeSW, _v1(5));
    _q1.Insert(SmallSE, _v1(6));
    _q1.Insert(LargeSE, _v1(7));

    ASSERT_EQ(_q1.Count(), 8);

    Area total = SmallNW
        .Union(LargeNW)
        .Union(SmallNE)
        .Union(LargeNE)
        .Union(SmallSW)
        .Union(LargeSW)
        .Union(SmallSE)
        .Union(LargeSE);

    total.Scale( Math::NextPower2(Math::Max(total.Width, total.Height, 1.0f)) );

    ASSERT_EQ(_q1.Bounds(), total);
}



