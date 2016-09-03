/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "EnumerationsGL.h"
#include "OpenGLAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        namespace Vertex { struct Standard; }

        class Entity3D : public IRenderableEntity
        {

            public:

                /** POSITION PROPERTIES **/
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



                /** ROTATION PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in degrees. </summary>
                virtual float Pitch()                                       const { return _world.Pitch(); }
                /// <summary> Gets the angle of rotation about the z-axis in degrees. </summary>
                virtual float Roll()                                        const { return _world.Roll(); }
                /// <summary> Gets the angle of rotation about the y-axis in degrees. </summary>
                virtual float Yaw()                                         const { return _world.Yaw(); }

                /// <summary> Sets the angle of rotation about the x-axis in degrees. </summary>
                virtual Entity3D& Pitch(float p)                                  { _world.Pitch(p); return *this; }
                /// <summary> Sets the angle of rotation about the z-axis in degrees. </summary>
                virtual Entity3D& Roll(float r)                                   { _world.Roll(r); return *this; }
                /// <summary> Sets the angle of rotation about the y-axis in degrees. </summary>
                virtual Entity3D& Yaw(float y)                                    { _world.Yaw(y); return *this; }



                /** SCALING PROPERTIES **/
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
                virtual const Vector3& Position()                           const { return _world.Position(); }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Entity3D& Position(const Vector3& p)                      { _world.Position(p); return *this; }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Entity3D& Position(float x, float y, float z = 0.0f)      { _world.Position(x, y, z); return *this; }

                virtual Entity3D& Rotate(const Vector3& r)                        { _world.Rotate(r); return *this; }

		        /// <summary> Gets the size of the entity in 3D space. </summary>
                virtual const Vector3& Scale() const                              { return _world.Scale(); }
		        /// <summary> Sets the size of the entity in 3D space. </summary>
                virtual Entity3D& Scale(const Vector3& s)                         { _world.Scale(s); return *this; }
		        /// <summary> Sets the size of the entity in 3D space. </summary>
                virtual Entity3D& Scale(float x, float y, float z = 1.0f)         { _world.Scale(x, y, z); return *this; }



		        /** RENDERABLE INTERFACE METHODS **/
                /// <summary> Gets a reference to the base color of the entity. </summary>
                virtual const Color4& Color()                               const override { return _color; }

                virtual const Array<uint>& Indices()                        const override { return _indices; }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture2D* Texture()                          const override { return _texture; }
                /// <summary> Gets the type of primitive that the vertices in the vertex array construct. </summary>
                virtual VertexTopologies Topology()                         const override { return _topology; }
                /// <summary> Gets a reference to the vertex array defining the geometry of an entity. </summary>
		        virtual const Array<Vertex::Standard>& Vertices()			const override { return _vertices; }
                /// <summary> Gets a reference to the world transformation matrix of an entity. </summary>
                /// <remarks>
                ///     The world transformation matrix defines the position, scale, and orientation of an entity in 3D space.
                /// </remarks>
                virtual const Transform& World()                            const override { return _world; }
                /// <summary> Gets whether this entity is visible in the rendered world. </summary>
                virtual bool IsVisible()                                    const override { return true; }

                /// <summary> Sets the base color of the entity. </summary>
                virtual Entity3D& Color(const Color4& color)                { _color = color; return *this; }



                /** DESTRUCTOR **/
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }



                /** UTILITIES **/
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual void Translate(float x, float y, float z = 0.0f)    { _world.Translate(x, y, z); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual void Translate(const Vector3& t)                    { _world.Translate(t); }

            protected:

                /** PROPERTY DATA **/
                Color4                      _color;
                Array<uint>                 _indices;
		        Texture2D*			        _texture;
                VertexTopologies            _topology;
		        Array<Vertex::Standard>		_vertices;
                Transform                   _world;



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new 3D renderable entity composed of white triangles. </summary>
                /// <param name="vertices"> The vertex array that defines the geometry of this entity. </param>
		        Entity3D(const Array<Vertex::Standard>& vertices) :
                    Entity3D(vertices, Array<uint>(0))
		        {

		        }

                Entity3D(const Array<Vertex::Standard>& vertices, const Array<uint>& indices) :
                    Entity3D(Color4::White, VertexTopologies::Triangles, vertices, indices)
                {

                }
                Entity3D(const Color4& color, VertexTopologies topology, const Array<Vertex::Standard>& vertices) :
                    Entity3D(color, topology, vertices, Array<uint>())
                {

                }
		        /// <summary> Constructs a new 3D renderable entity. </summary>
                /// <param name="color"> The base color of this entity's geometry. </param>
                /// <param name="topology"> The type of primitive that the vertices of this entity define. </param>
                /// <param name="vertices"> The vertex array that defines the geometry of this entity. </param>
                Entity3D(const Color4& color, VertexTopologies topology, const Array<Vertex::Standard>& vertices, const Array<uint>& indices) :
			        _color(color),
                    _indices(indices),
                    _texture(nullptr),
			        _topology(topology),
			        _vertices(vertices)
		        {

		        }

        };
    }
}
