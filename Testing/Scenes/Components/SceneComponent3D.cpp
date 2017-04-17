/* CHANGELOG
 * Written by Josh Grooms on 20170417
 */

#include "Scene3D.h"
#include "Components/SceneComponent3D.h"
#include <gtest/gtest.h>

using namespace Cyclone::Scenes;



class _SceneComponent3D : public ::testing::Test
{
    protected:

        SceneComponent3D    _c0;
        Scene3D             _s0;

        _SceneComponent3D() : 
            _c0(_s0)
        {

        }

};



/** CONSTRUCTION **/
TEST_F(_SceneComponent3D, DefaultConstruction)
{

}

