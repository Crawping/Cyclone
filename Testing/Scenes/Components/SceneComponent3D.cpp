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

        Scene3D      _s0;
        //SceneComponent3D    _c0;
        

        _SceneComponent3D()
            //_c0(_s0)
        {

        }

};



/** CONSTRUCTION **/
TEST_F(_SceneComponent3D, Construction)
{
    ASSERT_EQ(_s0.Bounds(), Volume::Empty);
    ASSERT_EQ(&(_s0.Parent()), &_s0);
    ASSERT_EQ(_s0.Transform(), Transform3D());
}

