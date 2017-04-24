/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#include "TypeDefinitions.h"
#include "IO/Console.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>
#include <typeinfo>

using namespace Cyclone::Reflection;



TEST(_Utilities, Booleans)
{
    ASSERT_TRUE(Meta::Boolean<true>());
    ASSERT_FALSE(Meta::Boolean<false>());
}
TEST(_Utilities, Conditionals)
{
    ASSERT_TRUE
    ((
        Meta::Conditional
        < 
            (5 > 3), 
            Meta::Boolean<true>, 
            Meta::Boolean<false>
        >()
    ));

    ASSERT_FALSE
    ((
        Meta::Conditional
        <
            (3 > 5),
            Meta::Boolean<true>,
            Meta::Boolean<false>
        >()
    ));
}
TEST(_Utilities, Dereferencing)
{
    ASSERT_STREQ(typeid(void).name(),               typeid(Meta::Dereference<void>::Type).name());
    ASSERT_STREQ(typeid(void).name(),               typeid(Meta::Dereference<void*>::Type).name());
    ASSERT_STREQ(typeid(char).name(),               typeid(Meta::Dereference<const char*>::Type).name());
    ASSERT_STREQ(typeid(string).name(),             typeid(Meta::Dereference<const string&>::Type).name());
}
TEST(_Utilities, EqualityTesting)
{
    ASSERT_EQ((Meta::IsEqual<int, double>()),       false);
}
TEST(_Utilities, IsPointer)
{
    ASSERT_EQ(Meta::IsPointer<int*>(),              true);
    ASSERT_EQ(Meta::IsPointer<const char*>(),       true);

    ASSERT_EQ(Meta::IsPointer<int>(),               false);
    ASSERT_EQ(Meta::IsPointer<char>(),              false);
    ASSERT_EQ(Meta::IsPointer<void>(),              false);
    ASSERT_EQ(Meta::IsPointer<const string&>(),     false);
}
TEST(_Utilities, IsReference)
{
    ASSERT_EQ(Meta::IsReference<int&>(),            true);
    ASSERT_EQ(Meta::IsReference<const string&>(),   true);

    ASSERT_EQ(Meta::IsReference<int>(),             false);
    ASSERT_EQ(Meta::IsReference<char>(),            false);
    ASSERT_EQ(Meta::IsReference<void>(),            false);
    ASSERT_EQ(Meta::IsReference<const char*>(),     false);
}
TEST(_Utilities, IsVoid)
{
    ASSERT_EQ(Meta::IsVoid<void>(),                 true);
    ASSERT_EQ(Meta::IsVoid<int>(),                  false);
}
TEST(_Utilities, SizeOf)
{
    ASSERT_EQ(Meta::SizeOf<void>(),                 0);
    ASSERT_EQ(Meta::SizeOf<int>(),                  sizeof(int));
    ASSERT_EQ(Meta::SizeOf<const string&>(),        sizeof(const string&));
    ASSERT_EQ(Meta::SizeOf<char*>(),                sizeof(char*));
}