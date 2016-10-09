/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture3D;
        namespace Vertex { struct Standard; }

        template<typename T>
        class Entity3D : public virtual IRenderable3D<T>
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

		        /// <summary> Gets the size of the entity in 3D space. </summary>
                virtual const Vector3& Scale() const                              { return _world.Scale(); }
		        /// <summary> Sets the size of the entity in 3D space. </summary>
                virtual Entity3D& Scale(const Vector3& s)                         { _world.Scale(s); return *this; }
		        /// <summary> Sets the size of the entity in 3D space. </summary>
                virtual Entity3D& Scale(float x, float y, float z = 1.0f)         { _world.Scale(x, y, z); return *this; }



		        /** RENDERABLE INTERFACE METHODS **/
                virtual const Volume& Bounds()                              const override { return _bounds; }
                /// <summary> Gets a reference to the base color of the entity. </summary>
                virtual const Color4& Color()                               const override { return _color; }
                /// <summary> Gets a reference to the array of indices that specify the vertex rendering order. </summary>
                virtual const Vector<uint>& Indices()                       const override { return _indices; }
                /// <summary> Gets whether this entity is visible in the rendered world. </summary>
                virtual bool IsVisible()                                    const override { return _isVisible; }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture3D* Texture()                          const override { return _texture; }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                virtual VertexTopologies Topology()                         const override { return _topology; }
                /// <summary> Gets a reference to the array of points that define the shape of an entity in 3D model space. </summary>
		        virtual const Vector<T>& Points()                           const override { return _points; }
                /// <summary> Gets a reference to the world transformation matrix of an entity. </summary>
                /// <remarks>
                ///     The world transform defines the position, scale, and orientation of an entity in 3D space. It is typically 
                ///     used to apply the rotation, scaling, and translation operations that place the geometry of an entity 
                ///     (defined by the <see cref="Points"/> method) into its correct position in a three-dimensional environment 
                ///     called 'world' space.
                /// </remarks>
                virtual const Transform& World()                            const override { return _world; }


                virtual Entity3D& Bounds(const Volume& bounds)              { _bounds = bounds; return *this; }
                /// <summary> Sets the base color of the entity. </summary>
                virtual Entity3D& Color(const Color4& color)                { _color = color; return *this; }
                /// <summary> Sets whether the entity is visible in a rendered scene. </summary>
                virtual Entity3D& IsVisible(bool value)                     { _isVisible = value; return *this; }

                virtual Entity3D& Texture(const Texture3D* texture)         { _texture = texture; return *this; }


                /** DESTRUCTOR **/
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }



                /** UTILITIES **/
                /// <summary> Sets the angles of rotation about the (x, y, z) axes in degrees. </summary>
                virtual Entity3D& Rotate(const Vector3& r)                  { _world.Rotate(r); return *this; }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual void Translate(float x, float y, float z = 0.0f)    { _world.Translate(x, y, z); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual void Translate(const Vector3& t)                    { _world.Translate(t); }

            protected:

                /** PROPERTY DATA **/
                Volume                  _bounds;
                Color4                  _color;
                Vector<uint>            _indices;
                bool                    _isVisible;
		        const Texture3D*		_texture;
                VertexTopologies        _topology;
		        Vector<T>		        _points;
                Transform               _world;



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
			        _color(color),
                    _indices(indices),
                    _isVisible(true),
			        _points(points),
                    _texture(nullptr),
			        _topology(topology)
		        {

		        }

        };
    }
}
