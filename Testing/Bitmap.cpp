/* CHANGELOG 
 * Written by Josh Grooms on 20160707
 */

#include <gtest/gtest.h>
#include "Bitmap.h"
#include "Color4.h"



class _Bitmap : public ::testing::Test
{
    protected:
        const static Vector2 BitmapSize;

        Bitmap _b1;
        Bitmap _b2;
        Bitmap _b3;

        _Bitmap() :
            _b1(Vector2::Zero),
            _b2(Vector2::One),
            _b3(BitmapSize)
        {
            _b3.Fill(Color4::Magenta);
            _b3(32, 64) = Color4::Cyan;
        }
};

const Vector2 _Bitmap::BitmapSize = Vector2(128, 256);



TEST_F(_Bitmap, ObjectConstruction)
{
    ASSERT_EQ(_b1.Size(), Vector2::Zero);
    ASSERT_EQ(_b1.IsEmpty(), true);
    ASSERT_EQ(_b1.Length(), 0);

    ASSERT_EQ(_b2.Size(), Vector2::One);
    ASSERT_EQ(_b2.IsEmpty(), false);
    ASSERT_EQ(_b2.Length(), 1);

    ASSERT_EQ(_b3.Size(), BitmapSize);
    ASSERT_EQ(_b3.IsEmpty(), false);
    ASSERT_EQ(_b3.Length(), BitmapSize.X * BitmapSize.Y);
}

TEST_F(_Bitmap, ObjectCopying)
{
    Bitmap copy(_b3);

    const Color4* originalPixels = _b3.ToArray();
    const Color4* copyPixels = copy.ToArray();
    ASSERT_NE(originalPixels, copyPixels);

    for (int a = 0; a < _b3.Length(); a++)
        ASSERT_EQ(originalPixels[a], copyPixels[a]);

    copy(32, 64) = Color4::Green;
    ASSERT_NE(_b3(32, 64), copy(32, 64));
}

TEST_F(_Bitmap, IndexingOperator)
{
    EXPECT_EQ(_b3(32, 64), Color4::Cyan);
    EXPECT_EQ(_b3(33, 64), Color4::Magenta);
}