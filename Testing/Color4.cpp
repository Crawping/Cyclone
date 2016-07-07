/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#include <gtest/gtest.h>
#include "Color4.h"



class _Color4 : public ::testing::Test
{
    protected:
        Color4 _c0;
        Color4 _c1;

        _Color4() :
            _c1(Color4::White)
        {

        }
};



TEST_F(_Color4, DefaultConstructor)
{
    EXPECT_EQ(_c0.A, 1.0f);
    EXPECT_EQ(_c0.B, 0.0f);
    EXPECT_EQ(_c0.G, 0.0f);
    EXPECT_EQ(_c0.R, 0.0f);
}

TEST_F(_Color4, EqualityOperators)
{
    EXPECT_EQ(_c0 == Color4::Black, true);
    EXPECT_EQ(_c0 == Color4::Blue, false);
    EXPECT_EQ(_c0 != Color4::Yellow, true);
    EXPECT_EQ(_c1, Color4::White);
    EXPECT_NE(_c1, Color4::Red);
}

TEST_F(_Color4, ToIntOperator)
{
    EXPECT_EQ(_c0.ToInt(), 255);
    EXPECT_EQ(_c1.ToInt(), 4294967295);
}

TEST_F(_Color4, ToStringOperator)
{
    //EXPECT_EQ(_c1.ToString(), "(1.000000, 1.000000, 1.000000, 1.000000)");
    //EXPECT_EQ(_c1.ToString(), colorStr);
}