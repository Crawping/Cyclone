/* CHANGELOG
 * Written by Josh Grooms on 20170604
 */

#include "Geometry/Entity3D.h"
#include "Resources/ResourceManager.h"
#include <gtest/gtest.h>

using namespace Cyclone::Scenes;



class  _ResourceManager: public testing::Test
{
    protected:

        ResourceManager _r0;

        _ResourceManager()
        {

        }

};



TEST_F(_ResourceManager, Construction)
{

}
TEST_F(_ResourceManager, Creation)
{
    auto r1 = _r0.Create<Geometry3D>();
    

}