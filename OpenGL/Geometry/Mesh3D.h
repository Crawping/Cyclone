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
        

        class Mesh3D : public Entity3D<Vector3>
        {
            public:

                Mesh3D(const Geometry3D& geometry) : Entity3D(geometry) { }

                void Add(const Vector3& vertex)
                {
                    Vertices.Append(vertex);
                }
                void Add(const IArray<Vector3>& vertices)
                {
                    Vertices.Append(vertices);
                }


            private:
                
                List<Vector3> Vertices;
        };
    }
}
