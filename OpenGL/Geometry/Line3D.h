/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Entity3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Line3D : public Entity3D<Vector3>
        {
            public:
                /// <summary> Constructs a new white-colored horizontal line spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                Line3D() : Entity3D(Geometry3D::Line()) { }
        };
    }
}
