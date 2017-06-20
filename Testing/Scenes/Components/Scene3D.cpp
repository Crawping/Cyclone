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


        _Scene3D()
        {

        }
};



TEST_F(_Scene3D, Construction)
{

    ASSERT_EQ(_s0.View(),   Camera());
}