/* CHANGELOG
 * Written by Josh Grooms on 20170628
 */

#include "Collections/Object.h"
#include "Spatial/Transform.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Object: public testing::Test
{
    protected:

        Object<Vector3, Vector4, int> _o0;
        Object<Transform3D, Vector2, int> _o1;



        _Object():
            _o1(Transform3D(Vector3(10)), Vector2(-5), 1024)
        {

        }
};



TEST_F(_Object, Construction)
{
    ASSERT_EQ(_o0.Count,    3);
    ASSERT_EQ( (Meta::IsA<Vector3, Object<Vector3, Vector4, int>::Types::Get<0>>()), true );
    ASSERT_EQ( (Object<Vector3, Vector4, int>::Types::IsEqual<Vector4>(1)), true );

    //ASSERT_EQ(_o0.Size,     sizeof(_o0));
    //ASSERT_EQ(_o1.Size,     sizeof(Object<int>));
}



TEST_F(_Object, Attributes)
{
    auto a1 = Object<Vector3, Vector4, int>::Attribute<1>();
    auto a2 = Object<Transform3D, Vector2, int>::Attribute<1>();
    
    ASSERT_EQ(a1(_o0),          Vector4());
    ASSERT_EQ(a2(_o1),          Vector2(-5));
}
TEST_F(_Object, Get)
{
    ASSERT_EQ(_o0.Get<0>(),     Vector3());
    ASSERT_EQ(_o0.Get<1>(),     Vector4());
    ASSERT_EQ(_o0.Get<2>(),     0);

    ASSERT_EQ(_o1.Get<0>(),     Transform3D(Vector3(10)));
    ASSERT_EQ(_o1.Get<1>(),     Vector2(-5));
    ASSERT_EQ(_o1.Get<2>(),     1024);
}
TEST_F(_Object, Property)
{
    _o1.Property<0>() = Transform3D(Vector3(10)).Translate(10);
    _o1.Property<1>() = Vector2(-1);
    _o1.Property<2>() = 2048;

    ASSERT_EQ(_o1.Property<0>(), Transform3D(Vector3(20)));
    ASSERT_EQ(_o1.Property<1>(), Vector2(-1));
    ASSERT_EQ(_o1.Property<2>(), 2048);
}