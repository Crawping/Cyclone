/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Entity3D.h"
#include "Spatial/Geometry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Line3D : public Entity3D
        {
            public: 
                Line3D() : Entity3D(Geometry::Quad()) { }
        };
    }
}
