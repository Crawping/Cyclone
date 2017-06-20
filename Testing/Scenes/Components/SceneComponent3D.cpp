/* CHANGELOG
 * Written by Josh Grooms on 20170417
 */

#include "Scene3D.h"
#include "Components/SceneComponent3D.h"
#include <gtest/gtest.h>

using namespace Cyclone::Scenes;
using namespace Cyclone::Utilities;






class _SceneComponent3D: public testing::Test
{
    protected:

        Scene3D             _s0;
        SceneComponent3D    _c0;


        Subscription<const IComponent&, const ISpatialTransform&> _sub1;
        
        

        _SceneComponent3D():
            _s0(),
            _c0(),
            EventTriggered(false)
        {
            _sub1 = _c0.OnTransformUpdate
            (
                Method
                <
                    void,
                    _SceneComponent3D,
                    const IComponent&,
                    const ISpatialTransform&
                >(this, &_SceneComponent3D::ProcessTransformUpdate)
            );
        }

        bool EventTriggered;
        void ProcessTransformUpdate(const IComponent& src, const ISpatialTransform& evt)
        {
            ASSERT_EQ(&_c0, &src);
            ASSERT_EQ(_c0.Transform().ToMatrix4x4(), evt.ToMatrix4x4());
            EventTriggered = true;
        }

};



/** CONSTRUCTION **/
TEST_F(_SceneComponent3D, Construction)
{

}
TEST_F(_SceneComponent3D, Events)
{
    auto t1 = _c0.Transform();
    ASSERT_EQ(EventTriggered, false);

    t1.Orientation(Vector3(1, 2, 3));
    _c0.Transform(t1);
    ASSERT_EQ(EventTriggered, true);
}

