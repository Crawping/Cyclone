/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#pragma once
#include "Imaging/Color4.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Geometry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Point3D : public Entity3D
        {
	        public:
                using Entity3D::Depth;
                using Entity3D::Height;
                using Entity3D::Width;



                /** PROPERTIES **/
                OpenGLAPI Point3D& Depth(float z)                             override;
                OpenGLAPI Point3D& Height(float y)                            override;
                OpenGLAPI Point3D& Width(float x)                             override;

                OpenGLAPI Point3D& Scale(const Vector3& value)                override;
                OpenGLAPI Point3D& Scale(float x, float y, float z = 1.0f)    override;



                /** CONSTRUCTOR **/
		        Point3D() : Entity3D(Color4::White, VertexTopologies::Points, Geometry::Point()) { }
        };
    }
}
