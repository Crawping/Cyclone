/* CHANGELOG
 * Written by Josh Grooms on 20150908
 */

#pragma once
/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#include "Primitives/Entity3D.h"
#include "Spatial/Geometry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Quad : public Entity3D
        {

            public:
                /** CONSTRUCTOR **/
                Quad() : Entity3D(Geometry::Quad) { }

        };
    }
}