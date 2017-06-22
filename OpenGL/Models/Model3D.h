/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Geometry/Geometry3D.h"
#include "Geometry/Vertex.h"
#include "Interfaces/IModel.h"
#include "Resources/Resource.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Model3D:
            public virtual IModel,
            public ITransformable3D
        {
            public:

                /** PROPERTIES **/
                virtual const Volume& Bounds()              const { return _geometry->Bounds(); }
                /// <summary> Gets the geometric data that define the shape of the mesh. </summary>
                Resource<IGeometric> Geometry()             const override { return _geometry; }

                const Vector3& Orientation()                const override { return _transform.Orientation(); }
                const Vector3& Position()                   const override { return _transform.Position(); }
                const Vector3& Scale()                      const override { return _transform.Scale(); }
                virtual PointTopologies Topology()          const { return _geometry->Topology(); }
                const Transform3D& Transform()              const override { return _transform; }

                /// <summary> Sets the geometric data that define the shape of the mesh. </summary>
                //OpenGLAPI virtual Model3D& Geometry(const Geometry3D& value);
                OpenGLAPI virtual Model3D& Geometry(Component<Geometry3D> value);
                OpenGLAPI virtual Model3D& Transform(const Transform3D& value);
                OpenGLAPI Model3D& Orientation(const Vector3& value);
                OpenGLAPI Model3D& Position(const Vector3& value);
                OpenGLAPI Model3D& Scale(const Vector3& value);


                /** CONSTRUCTORS **/
                /// <summary> Constructs a new empty 3D mesh for rendering models in scenes. </summary>
                OpenGLAPI Model3D();
                /// <summary> Constructs a new 3D mesh that is initialized with pre-defined geometric data. </summary>
                /// <param name="geometry"> An existing 3D geometry data object. </param>
                OpenGLAPI Model3D(Resource<Geometry3D> geometry);

            private:
            
                /** DATA **/
                Resource<Geometry3D>    _geometry;
                Transform3D             _transform;

        };
    }
}
