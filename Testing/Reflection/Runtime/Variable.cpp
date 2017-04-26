/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#include "Runtime/Variable.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;
using namespace Cyclone::Utilities;



class _Variable : public testing::Test
{
    protected:

        string _d1;


        Variable _v0;
        Variable _v1;
        Variable _v2;
        Variable _v3;


        _Variable() :
            _d1("Testing"),
            _v1(10),
            _v2("Testing"),
            _v3(_d1)
        {

        }
};



/** CONSTRUCTION **/
TEST_F(_Variable, Properties)
{
    ASSERT_EQ(_v1.IsConstant(),         false);
    ASSERT_EQ(_v1.IsPointer(),          false);
    ASSERT_EQ(_v1.IsReference(),        false);

    ASSERT_EQ(_v2.IsConstant(),         true);
    ASSERT_EQ(_v2.IsPointer(),          true);
    ASSERT_EQ(_v2.IsReference(),        false);

    ASSERT_EQ(_v3.IsConstant(),         false);
    ASSERT_EQ(_v3.IsPointer(),          false);
    ASSERT_EQ(_v3.IsReference(),        true);
}



/** UTILITIES **/
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



/** OPERATORS **/
TEST_F(_Variable, Assignment)
{
    Variable v1 = _v1;
    Variable v2 = _v2;
    Variable v3 = _v3;

    ASSERT_EQ(v1.Type(),                Meta::TypeOf(10));
    ASSERT_EQ(v2.Type(),                Meta::TypeOf("T"));
    ASSERT_EQ(v3.Type(),                Meta::TypeOf(_d1));
    ASSERT_NE(v2.Type(),                Meta::TypeOf('T'));

    v1 = "New Test";
    v2 = &v1;
    v3 = 3.14159265;

    ASSERT_NE(v1.Type(),                Meta::TypeOf(10));
    ASSERT_NE(v2.Type(),                Meta::TypeOf("T"));
    ASSERT_NE(v3.Type(),                Meta::TypeOf(_d1));

    ASSERT_EQ(v1.Type(),                Meta::TypeOf("T"));
    ASSERT_EQ(v2.Type(),                Meta::TypeOf(&v1));
    ASSERT_EQ(v3.Type(),                Meta::TypeOf(3.14));
}
TEST_F(_Variable, Copying)
{
    Variable v1 = _v1;
    Variable v2 = _v2;
    Variable v3 = _v3;

    ASSERT_EQ(v1,                       _v1);
    ASSERT_EQ(v2,                       _v2);
    ASSERT_EQ(v3,                       _v3);

    ASSERT_NE(v1,                       _v2);
    ASSERT_NE(v1,                       _v3);
    ASSERT_NE(v2,                       _v1);
    ASSERT_NE(v2,                       _v3);
}