/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#include "TypeDefinitions.h"
#include "IO/Console.h"
#include "Reflection/Metafunctions.h"
#include <gtest/gtest.h>
#include <typeinfo>

using namespace Cyclone::Utilities;



TEST(_Metafunctions, Dereferencing)
{
    ASSERT_STREQ(typeid(void).name(),       typeid(Dereference<void>::Class).name());
    ASSERT_STREQ(typeid(void).name(),       typeid(Dereference<void*>::Class).name());
    ASSERT_STREQ(typeid(char).name(),       typeid(Dereference<const char*>::Class).name());
    ASSERT_STREQ(typeid(string).name(),     typeid(Dereference<const string&>::Class).name());
}
TEST(_Metafunctions, EqualityTesting)
{
    ASSERT_EQ((IsEqual<int, double>()),     false);
}
TEST(_Metafunctions, IsPointer)
{
    ASSERT_EQ(IsPointer<int*>(),            true);
    ASSERT_EQ(IsPointer<const char*>(),     true);

    ASSERT_EQ(IsPointer<int>(),             false);
    ASSERT_EQ(IsPointer<char>(),            false);
    ASSERT_EQ(IsPointer<void>(),            false);
    ASSERT_EQ(IsPointer<const string&>(),   false);
}
TEST(_Metafunctions, IsReference)
{
    ASSERT_EQ(IsReference<int&>(),          true);
    ASSERT_EQ(IsReference<const string&>(), true);

    ASSERT_EQ(IsReference<int>(),           false);
    ASSERT_EQ(IsReference<char>(),          false);
    ASSERT_EQ(IsReference<void>(),          false);
    ASSERT_EQ(IsReference<const char*>(),   false);
}
TEST(_Metafunctions, IsVoid)
{
    ASSERT_EQ(IsVoid<void>(),               true);
    ASSERT_EQ(IsVoid<int>(),                false);
}