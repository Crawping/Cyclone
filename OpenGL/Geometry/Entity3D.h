/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "EnumerationsGL.h"
#include "Geometry/GeometricEntity3D.h"
#include "GL/OpenGLAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Libraries/Material3D.h"
#include "Spatial/Transform.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture3D;


        template<typename T>
        class Entity3D : 
            public GeometricEntity3D<T>,
            public virtual IRenderable3D<T>
        {

            public:

		        /** RENDERABLE INTERFACE METHODS **/

                virtual const List<IRenderable3D<T>*>& Components()     const override { return _components; }
                /// <summary> Gets whether this entity is visible in the rendered world. </summary>
                virtual bool IsVisible()                                const override { return _isVisible; }
                /// <summary> Gets a reference to the primary color of the entity. </summary>
                virtual const Color4& PrimaryColor()                    const override { return _material.PrimaryColor(); }
                /// <summary> Gets a reference to the secondary color of the entity. </summary>
                virtual const Color4& SecondaryColor()                  const override { return _material.SecondaryColor(); }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture3D* Texture()                      const override { return _material.Texture(); }

                /// <summary> Sets whether the entity is visible in a rendered scene. </summary>
                virtual Entity3D& IsVisible(bool value)                 { _isVisible = value; return *this; }
                /// <summary> Sets the primary color of the entity. </summary>
                virtual Entity3D& PrimaryColor(const Color4& value)     { _material.PrimaryColor(value); return *this; }
                /// <summary> Sets the secondary color of the entity. </summary>
                virtual Entity3D& SecondaryColor(const Color4& value)   { _material.SecondaryColor(value); return *this; }
                /// <summary> Sets the texture to be used when rendering the entity (NOT YET IMPLEMENTED). </summary>
                virtual Entity3D& Texture(const Texture3D* value)       { _material.Texture(value); return *this; }



                /** DESTRUCTOR **/
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }

            protected:

                /** PROPERTY DATA **/
                bool                    _isVisible;
                List<IRenderable3D<T>*> _components;



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new 3D renderable entity composed of white triangles. </summary>
                /// <param name="points"> The array of points that define the geometry of this entity. </param>
		        Entity3D(const Vector<T>& points) :
                    Entity3D(points, Vector<uint>(0))
		        {

		        }

                Entity3D(const Vector<T>& points, const Vector<uint>& indices) :
                    Entity3D(Color4::White, VertexTopologies::Triangles, points, indices)
                {

                }
                Entity3D(const Color4& color, VertexTopologies topology, const Vector<T>& points) :
                    Entity3D(color, topology, points, Vector<uint>())
                {

                }
		        /// <summary> Constructs a new 3D renderable entity. </summary>
                /// <param name="color"> The base color of this entity's geometry. </param>
                /// <param name="topology"> The type of primitive that the vertices of this entity define. </param>
                /// <param name="points"> The array of points that define the geometry of this entity. </param>
                Entity3D(const Color4& color, VertexTopologies topology, const Vector<T>& points, const Vector<uint>& indices) :
                    GeometricEntity3D(topology, points, indices),
                    _isVisible(true)
		        {
                    _material.PrimaryColor(color);
		        }

            private:
                
                /** PROPERTY DATA **/
                Material3D              _material;

        };
    }
}
