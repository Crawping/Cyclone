/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#include "IO/Console.h"
#include "Metaclass.h"
#include "Math/Vector4.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;


class _Metaclass : public testing::Test
{
    protected:

        const Metaclass& _t1;
        const Metaclass& _t2;
        const Metaclass& _t3;
        const Metaclass& _t4;



        _Metaclass() :
            _t1(Metaclass::Get<void>()),
            _t2(Metaclass::Get<int>()),
            _t3(Metaclass::Get<string&>()),
            _t4(Metaclass::Get<const char*>())
        {
            
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_Metaclass, Construction)
{
    ASSERT_EQ(_t1.ID(),             typeid(void).hash_code());
    ASSERT_EQ(_t1.IsReference(),    false);
    ASSERT_EQ(_t1.IsPointer(),      false);
    ASSERT_EQ(_t1.Name(),           "void");
    ASSERT_EQ(_t1.Size(),           0);

    ASSERT_EQ(_t2.ID(),             typeid(int).hash_code());
    ASSERT_EQ(_t2.IsReference(),    false);
    ASSERT_EQ(_t2.IsPointer(),      false);
    ASSERT_EQ(_t2.Name(),           "int");
    ASSERT_EQ(_t2.Size(),           sizeof(int));

    ASSERT_EQ(_t3.ID(),             typeid(string).hash_code());
    ASSERT_EQ(_t3.IsConstant(),     false);
    ASSERT_EQ(_t3.IsPointer(),      false);
    ASSERT_EQ(_t3.IsReference(),    true);
    ASSERT_EQ(_t3.Name(),           typeid(string).name());
    ASSERT_EQ(_t3.CoreSize(),       sizeof(string));

    ASSERT_EQ(_t4.ID(),             typeid(char).hash_code());
    ASSERT_EQ(_t4.IsConstant(),     true);
    ASSERT_EQ(_t4.IsPointer(),      true);
    ASSERT_EQ(_t4.IsReference(),    false);
    ASSERT_EQ(_t4.Name(),           typeid(char).name());
    ASSERT_EQ(_t4.CoreSize(),       sizeof(char));
}



/** UTILITY TESTS **/
TEST_F(_Metaclass, Cast)
{

}
TEST_F(_Metaclass, Get)
{
    ASSERT_EQ(Metaclass::IsClass<int>(),        true);
    ASSERT_EQ(Metaclass::IsClass<int&>(),       true);
    ASSERT_EQ(Metaclass::IsClass<void>(),       true);
    ASSERT_EQ(Metaclass::IsClass<void*>(),      true);

    ASSERT_EQ(Metaclass::IsClass<Metaclass>(),  false);
    ASSERT_EQ(Metaclass::IsClass<Vector4>(),    false);
}