/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once

#include "Color4.h"
#include "IRenderable.h"
#include "EnumerationsGL.h"
#include "OpenGLAPI.h"
#include "Transform.h"

class ShaderPipeline;



class Entity3D : public IRenderableEntity
{

    public:

        /** PROPERTIES **/
        /// <summary> Gets the position of the entity along the world x-axis. </summary>
        virtual float X()                                           const { return _world.X(); }
		/// <summary> Gets the position of the entity along the world y-axis. </summary>
        virtual float Y()                                           const { return _world.Y(); }
		/// <summary> Gets the position of the entity along the world z-axis. </summary>
        virtual float Z()                                           const { return _world.Z(); }

		/// <summary> Sets the position of the entity along the world x-axis. </summary>
        virtual Entity3D& X(float x)                                      { _world.X(x); return *this; }
		/// <summary> Sets the position of the entity along the world y-axis. </summary>
        virtual Entity3D& Y(float y)                                      { _world.Y(y); return *this; }
		/// <summary> Sets the position of the entity along the world z-axis. </summary>
        virtual Entity3D& Z(float z)                                      { _world.Z(z); return *this; }

		/// <summary> Gets the size of the entity along the z-axis. </summary>
        virtual float Depth()                                       const { return _world.ScaleZ(); }
		/// <summary> Gets the size of the entity along the y-axis. </summary>
        virtual float Height()                                      const { return _world.ScaleY(); }
		/// <summary> Gets the size of the entity along the x-axis. </summary>
        virtual float Width()                                       const { return _world.ScaleX(); }

		/// <summary> Sets the size of the entity along the z-axis. </summary>
        virtual Entity3D& Depth(float z)                                  { _world.ScaleZ(z); return *this; }
		/// <summary> Sets the size of the entity along the y-axis. </summary>
        virtual Entity3D& Height(float y)                                 { _world.ScaleY(y); return *this; }
		/// <summary> Sets the size of the entity along the x-axis. </summary>
        virtual Entity3D& Width(float x)                                  { _world.ScaleX(x); return *this; }

		/// <summary> Gets the position of the entity in 3D world coordinates. </summary>
        virtual Vector3 Position()                                  const { return _world.Position(); }
		/// <summary> Sets the position of the entity in 3D world coordinates. </summary>
        virtual Entity3D& Position(const Vector3& p)                      { _world.Position(p); return *this; }
		/// <summary> Sets the position of the entity in 3D world coordinates. </summary>
        virtual Entity3D& Position(float x, float y, float z = 0.0f)      { _world.Position(x, y, z); return *this; }

		/// <summary> Gets the size of the entity in 3D space. </summary>
        virtual Vector3 Scale() const                                     { return _world.Scale(); }
		/// <summary> Sets the size of the entity in 3D space. </summary>
        virtual Entity3D& Scale(const Vector3& s)                         { _world.Scale(s); return *this; }
		/// <summary> Sets the size of the entity in 3D space. </summary>
        virtual Entity3D& Scale(float x, float y, float z = 1.0f)         { _world.Scale(x, y, z); return *this; }



		/** RENDERABLE INTERFACE METHODS **/
        virtual const Color4& Color()                               const override { return _color; }
		virtual const Texture2D* Texture()                          const override { return nullptr; }
		virtual const Array<Vertex>& Vertices()						const override { return _vertices; }
        virtual const Transform& World()                            const override { return _world; }
        virtual bool IsVisible()                                    const override { return true; }



        /** DESTRUCTOR **/
        virtual ~Entity3D() { }



        /** UTILITIES **/
        /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
        virtual void Translate(float x, float y, float z = 0.0f)    { _world.Translate(x, y, z); }

    protected:

        /** DATA **/
        Color4              _color;

		Texture2D*			_texture;
		/// <summary> The type of primitive that the vertices in the vertex buffer construct. </summary>
        VertexTopologies    _topology;

		Array<Vertex>		_vertices;
		/// <summary> The matrix containing the position and any affine transformations of the entity in 3D space. </summary>
        Transform           _world;



        /** CONSTRUCTOR **/

		Entity3D(const Array<Vertex>& vertices) :
			_vertices(vertices)
		{
		
		}
		/// <summary> Constructs an empty 3D entity that must be completely initialized by a derived class. </summary>
        Entity3D(const Color4& color, VertexTopologies topology, const Array<Vertex>& vertices) : 
			_color(color),
			_topology(topology),
			_vertices(vertices)
		{ 
		
		}

};
