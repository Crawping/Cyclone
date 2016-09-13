/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Entity3D.h"
#include "Geometry/Geometry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Line3D : public Entity3D
        {
            public:
                /// <summary> Constructs a new white-colored horizontal line spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                Line3D() : Entity3D(Color4::White, VertexTopologies::Lines, Geometry::Line()) { }
        };
    }
}
