/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#include "IO/Console.h"
#include "Reflection/Type.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;


class _Type : public testing::Test
{
    protected:

        Type _t1;
        Type _t2;

        _Type() :
            _t1(Type::Create<void>()),
            _t2(Type::Create<int>())
        {
            
        }

};



TEST_F(_Type, VoidType)
{
    ASSERT_EQ(_t1.ID(),             typeid(void).hash_code());
    ASSERT_EQ(_t1.IsReference(),    false);
    ASSERT_EQ(_t1.IsPointer(),      false);
    ASSERT_EQ(_t1.Name(),           "void");
    ASSERT_EQ(_t1.Size(),           0);
}
TEST_F(_Type, TypeConstruction)
{
    ASSERT_EQ(_t2.ID(),             typeid(int).hash_code());
    ASSERT_EQ(_t2.IsReference(),    false);
    ASSERT_EQ(_t2.IsPointer(),      false);
    ASSERT_EQ(_t2.Name(),           "int");
    ASSERT_EQ(_t2.Size(),           sizeof(int));
    
}