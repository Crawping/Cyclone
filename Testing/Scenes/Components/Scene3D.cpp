/* CHANGELOG 
 * Written by Josh Grooms on 20170619
 */

#include "Scene3D.h"
#include <gtest/gtest.h>

using namespace Cyclone::Scenes;
using namespace Cyclone::Utilities;



class _Scene3D: public testing::Test
{
    protected:

        Scene3D _s0;

        Subscription<const Scene3D&, const Camera&>     _sub1;

        _Scene3D():
            EventTriggered(false)
        {
            _sub1 = _s0.OnViewUpdate
            (
                Method
                <
                    void,
                    _Scene3D,
                    const Scene3D&,
                    const Camera&
                >(this, &_Scene3D::ProcessViewUpdate)
            );
        }

        bool EventTriggered;
        void ProcessViewUpdate(const Scene3D& src, const Camera& evt)
        {
            ASSERT_EQ(&_s0, &src);
            ASSERT_EQ(_s0.View(), evt);
            EventTriggered = true;
        }
};



TEST_F(_Scene3D, Construction)
{
    ASSERT_EQ(_s0.Bounds(),             Volume::Empty);
    ASSERT_EQ(_s0.IsEmpty(),            true);
    ASSERT_EQ(_s0.IsVisible(),          true);
    ASSERT_EQ(_s0.View(),               Camera());
}
TEST_F(_Scene3D, Events)
{
    auto view = _s0.View();
    ASSERT_EQ(EventTriggered, false);

    view.Translate(10);
    _s0.View(view);
    ASSERT_EQ(EventTriggered, true);
}