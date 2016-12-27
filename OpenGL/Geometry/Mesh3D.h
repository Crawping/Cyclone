/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Collections/List.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Vertex.h"



namespace Cyclone
{
    namespace OpenGL
    {


        class Mesh3D : public Entity3D
        {
            public:

                Mesh3D() { }
                Mesh3D(const Geometry3D& geometry) : Entity3D(geometry) { }                
        };
    }
}
