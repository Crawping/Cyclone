/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Primitives/Entity3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Mesh3D : public Entity3D
        {
            public:

                Mesh3D(const Array<Vertex> vertices) : Entity3D(vertices) { }


        };
    }
}