/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#include "Meta/Variable.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;
using namespace Cyclone::Utilities;



class _Variable : public testing::Test
{
    protected:

        Variable _v0;
        Variable _v1;
        Variable _v2;


        _Variable() :
            _v1(10),
            _v2("Testing")
        {

        }
};



TEST_F(_Variable, Casting)
{
    ASSERT_TRUE(_v1.Cast<int>());
    ASSERT_FALSE(_v1.Cast<uint>());
    ASSERT_FALSE(_v1.Cast<string>());
    ASSERT_FALSE(_v1.Cast<char*>());
    ASSERT_FALSE(_v1.Cast<const string&>());

    ASSERT_TRUE(_v2.Cast<const char*>());
    ASSERT_FALSE(_v2.Cast<int>());

    auto v1 = *_v1.Cast<int>();
    ASSERT_EQ((int)v1, 10);
}