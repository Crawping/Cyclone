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
        class Point3D : public Entity3D<Vertex::Standard>
        {
	        public:
                using Entity3D::Depth;
                using Entity3D::Height;
                using Entity3D::Width;



                /** PROPERTIES **/
                /// <summary> Sets the size of the point along the world space z-axis. </summary>
                /// <remarks>
                ///     Currently, points in OpenGL may only have a uniform size in all three spatial dimensions, unless 
                ///     custom-written shaders are available to produce different effects. Thus, attempting to set the 
                ///     scale of a point along any world-space axis will result in that value being copied over to the 
                ///     other two dimensions via the function <see cref="glPointSize"/>.
                /// </remarks>
                OpenGLAPI Point3D& Depth(float z)                             override;
                /// <summary> Sets the size of the point along the world space y-axis. </summary>
                /// <remarks>
                ///     Currently, points in OpenGL may only have a uniform size in all three spatial dimensions, unless 
                ///     custom-written shaders are available to produce different effects. Thus, attempting to set the 
                ///     scale of a point along any world-space axis will result in that value being copied over to the 
                ///     other two dimensions via the function <see cref="glPointSize"/>.
                /// </remarks>
                OpenGLAPI Point3D& Height(float y)                            override;
                /// <summary> Sets the size of the point along the world space x-axis. </summary>
                /// <remarks>
                ///     Currently, points in OpenGL may only have a uniform size in all three spatial dimensions, unless 
                ///     custom-written shaders are available to produce different effects. Thus, attempting to set the 
                ///     scale of a point along any world-space axis will result in that value being copied over to the 
                ///     other two dimensions via the function <see cref="glPointSize"/>.
                /// </remarks>
                OpenGLAPI Point3D& Width(float x)                             override;

                /// <summary> Sets the size of the point in 3D world space. </summary>
                /// <remarks>
                ///     Currently, points in OpenGL may only have a uniform size in all three spatial dimensions, unless 
                ///     custom-written shaders are available to produce different effects. Thus, attempting to set the 
                ///     scale of a point along any world-space axis will result in that value being copied over to the 
                ///     other two dimensions via the function <see cref="glPointSize"/>.
                /// </remarks>
                OpenGLAPI Point3D& Scale(const Vector3& value)                override;
                /// <summary> Sets the size of the point in 3D world space. </summary>
                /// <remarks>
                ///     Currently, points in OpenGL may only have a uniform size in all three spatial dimensions, unless 
                ///     custom-written shaders are available to produce different effects. Thus, attempting to set the 
                ///     scale of a point along any world-space axis will result in that value being copied over to the 
                ///     other two dimensions via the function <see cref="glPointSize"/>.
                /// </remarks>
                OpenGLAPI Point3D& Scale(float x, float y, float z = 1.0f)    override;



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new white-colored point at the origin in 3D space. </summary>
		        Point3D() : Entity3D(Color4::White, VertexTopologies::Points, Geometry::Point()) { }
        };
    }
}
