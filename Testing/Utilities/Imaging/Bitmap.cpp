/* CHANGELOG 
 * Written by Josh Grooms on 20160707
 */

#include <gtest/gtest.h>
#include "Imaging/Bitmap.h"
#include "Imaging/Color4.h"

using namespace Cyclone::Utilities;



class _Bitmap : public ::testing::Test
{
    protected:
        const static Vector3 BitmapSize;

        Bitmap _b1;
        Bitmap _b2;
        Bitmap _b3;

        _Bitmap() :
            _b1(Vector3::Zero),
            _b2(Vector3::One),
            _b3(BitmapSize)
        {
            _b3.Fill(Color4::Magenta);
            _b3(32, 64, 0) = Color4::Cyan;
        }
};

const Vector3 _Bitmap::BitmapSize = Vector3(128, 256, 1);



TEST_F(_Bitmap, ObjectConstruction)
{
    ASSERT_EQ(_b1.Size(), Vector3::Zero);
    ASSERT_EQ(_b1.IsEmpty(), true);
    ASSERT_EQ(_b1.Count(), 0);

    ASSERT_EQ(_b2.Size(), Vector3::One);
    ASSERT_EQ(_b2.IsEmpty(), false);
    ASSERT_EQ(_b2.Count(), 1);

    ASSERT_EQ(_b3.Size(), BitmapSize);
    ASSERT_EQ(_b3.IsEmpty(), false);
    ASSERT_EQ(_b3.Count(), BitmapSize.X * BitmapSize.Y);
}

TEST_F(_Bitmap, ObjectCopying)
{
    Bitmap copy(_b3);

    const Color4* originalPixels = _b3.ToArray();
    const Color4* copyPixels = copy.ToArray();
    ASSERT_NE(originalPixels, copyPixels);

    for (int a = 0; a < _b3.Count(); a++)
        ASSERT_EQ(originalPixels[a], copyPixels[a]);

    copy(32, 64) = Color4::Green;
    ASSERT_NE(_b3(32, 64), copy(32, 64));
}

TEST_F(_Bitmap, IndexingOperator)
{
    EXPECT_EQ(_b3(32, 64), Color4::Cyan);
    EXPECT_EQ(_b3(33, 64), Color4::Magenta);
}