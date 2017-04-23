/* CHANGELOG
 * Written by Josh Grooms on 20170420
 */

#include "Imaging/Color4.h"
#include "Math/Vector4.h"
#include "Reflection/Field.h"
#include "Reflection/Metaclass.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class TestStructure { }; /*: public Meta::Structure
<
    Meta::Primitive<Color4, Color4(0.1f, 0.2f, 0.3f, 1.0f)>,
    Meta::Primitive<Vector4, Vector4(1.0f)>,
    Meta::Primitive<int, -10>,
    Meta::Primitive<ulong, 1000>
> { };*/



class _TestStructure : public testing::Test 
{
    protected:

        TestStructure   _s1;
        Color4          _c1;

        _TestStructure() 
            //_s1{ Color4::Black, Vector4::One, 0, 10 }
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

    //_s1.Get(0);
}