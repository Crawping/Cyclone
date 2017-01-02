/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Mesh3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Line3D : public Mesh3D
        {
            public:
                /// <summary> Constructs a new white-colored horizontal line spanning the coordinates (-0.5, 0, 0) to (0.5, 0, 0). </summary>
                Line3D() : Mesh3D(Geometry3D::Line()) { }
        };
    }
}
