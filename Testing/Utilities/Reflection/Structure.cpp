/* CHANGELOG
 * Written by Josh Grooms on 20170420
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Reflection/Field.h"
#include "Reflection/Metaclass.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;




class TestStructure
{
    public:
        Color4  _c1;
        Vector4 _v1;
        int     _i1;
        uint    _u1;
};



class _TestStructure : public testing::Test 
{
    protected:

        TestStructure   _s1;
        Color4          _c1;

        _TestStructure() :
            _s1{ Color4::Black, Vector4::One, 0, 10 }
        {
            Metaclass::Create<TestStructure>();
            Metaclass::Create<Color4>();
        }
};



/** CONSTRUCTION TESTS **/
TEST_F(_TestStructure, Construction)
{
    ASSERT_EQ(Metaclass::IsClass<Color4>(),         true);
    ASSERT_EQ(Metaclass::IsClass<TestStructure>(),  true);
}