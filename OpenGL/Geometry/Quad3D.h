/* CHANGELOG
 * Written by Josh Grooms on 20150908
 */

#pragma once
#include "Geometry/Entity3D.h"
#include "Geometry/Geometry3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Quad3D : public Entity3D<Vertex::Standard>
        {

            public:
                /** CONSTRUCTOR **/
                Quad3D() : Entity3D(Geometry3D::Quad()) { }

        };
    }
}
