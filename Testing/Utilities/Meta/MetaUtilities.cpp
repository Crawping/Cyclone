/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#include "TypeDefinitions.h"
#include "IO/Console.h"
#include "Meta/Utilities.h"
#include <gtest/gtest.h>
#include <typeinfo>

using namespace Cyclone::Utilities;



TEST(_MetaUtilities, Booleans)
{
    ASSERT_TRUE(Meta::Boolean<true>());
    ASSERT_FALSE(Meta::Boolean<false>());
}
TEST(_MetaUtilities, Conditionals)
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
TEST(_MetaUtilities, Dereferencing)
{
    ASSERT_STREQ(typeid(void).name(),               typeid(Meta::Dereference<void>::Type).name());
    ASSERT_STREQ(typeid(void).name(),               typeid(Meta::Dereference<void*>::Type).name());
    ASSERT_STREQ(typeid(char).name(),               typeid(Meta::Dereference<const char*>::Type).name());
    ASSERT_STREQ(typeid(string).name(),             typeid(Meta::Dereference<const string&>::Type).name());
}
TEST(_MetaUtilities, EqualityTesting)
{
    ASSERT_EQ((Meta::IsEqual<int, double>()),       false);
    ASSERT_EQ((Meta::IsEqual<int, uint>()),         false);
    ASSERT_EQ((Meta::IsEqual<uint, uint>()),        true);
    ASSERT_EQ(Meta::TypeEquals<int>(3.14159),       false);
}
TEST(_MetaUtilities, IsA)
{
    ASSERT_EQ((Meta::IsA<int, int>()),              true);
    ASSERT_EQ((Meta::IsA<int, string>()),           false);
}
TEST(_MetaUtilities, IsPointer)
{
    ASSERT_EQ(Meta::IsPointer<int*>(),              true);
    ASSERT_EQ(Meta::IsPointer<const char*>(),       true);

    ASSERT_EQ(Meta::IsPointer<int>(),               false);
    ASSERT_EQ(Meta::IsPointer<char>(),              false);
    ASSERT_EQ(Meta::IsPointer<void>(),              false);
    ASSERT_EQ(Meta::IsPointer<const string&>(),     false);
}
TEST(_MetaUtilities, IsReference)
{
    ASSERT_EQ(Meta::IsReference<int&>(),            true);
    ASSERT_EQ(Meta::IsReference<const string&>(),   true);

    ASSERT_EQ(Meta::IsReference<int>(),             false);
    ASSERT_EQ(Meta::IsReference<char>(),            false);
    ASSERT_EQ(Meta::IsReference<void>(),            false);
    ASSERT_EQ(Meta::IsReference<const char*>(),     false);
}
TEST(_MetaUtilities, IsVoid)
{
    ASSERT_EQ(Meta::IsVoid<void>(),                 true);
    ASSERT_EQ(Meta::IsVoid<int>(),                  false);
}
TEST(_MetaUtilities, SizeOf)
{
    ASSERT_EQ(Meta::SizeOf<void>(),                 0);
    ASSERT_EQ(Meta::SizeOf<int>(),                  sizeof(int));
    ASSERT_EQ(Meta::SizeOf<const string&>(),        sizeof(const string&));
    ASSERT_EQ(Meta::SizeOf<char*>(),                sizeof(char*));
}