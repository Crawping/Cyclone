/* CHANGELOG
 * Written by Josh Grooms on 20160706 
 */

#pragma once
#include "Imaging/Color4.h"
#include "Primitives/Entity3D.h"
#include "Spatial/Geometry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Point3D : public Entity3D
        {
	        public:
		        Point3D() : Entity3D(Color4::White, VertexTopologies::Points, Geometry::Point()) { }
        };
    }
}