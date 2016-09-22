/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Entity3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Mesh3D : public Entity3D<Vertex::Standard>
        {
            public:
                Mesh3D(const Vector<Vertex::Standard>& vertices) : Entity3D(vertices) { }

                Mesh3D(const Vector<Vertex::Standard>& vertices, const Vector<uint>& indices) :
                    Entity3D(vertices, indices)
                {

                }
        };
    }
}
