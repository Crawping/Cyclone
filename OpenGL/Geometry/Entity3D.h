/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "EnumerationsGL.h"
#include "Geometry/Geometry3D.h"
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
            public virtual IRenderable3D<T>
        {

            public:

                /** POSITIONAL PROPERTIES **/
                /// <summary> Gets the position of the entity along the world x-axis. </summary>
                virtual float X()                           const { return Position().X; }
		        /// <summary> Gets the position of the entity along the world y-axis. </summary>
                virtual float Y()                           const { return Position().Y; }
		        /// <summary> Gets the position of the entity along the world z-axis. </summary>
                virtual float Z()                           const { return Position().Z; }

		        /// <summary> Sets the position of the entity along the world x-axis. </summary>
                virtual Entity3D& X(float x)                { return Position(x, Y(), Z()); }
		        /// <summary> Sets the position of the entity along the world y-axis. </summary>
                virtual Entity3D& Y(float y)                { return Position(X(), y, Z()); }
		        /// <summary> Sets the position of the entity along the world z-axis. </summary>
                virtual Entity3D& Z(float z)                { return Position(X(), Y(), z); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                       const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                        const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                         const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual Entity3D& Pitch(float p)            { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual Entity3D& Roll(float r)             { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual Entity3D& Yaw(float y)              { return Orientation(Pitch(), y, Roll()); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                       const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                      const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                       const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual Entity3D& Depth(float z)            { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual Entity3D& Height(float y)           { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual Entity3D& Width(float x)            { return Scale(x, Height(), Depth()); }


                
                /** BATCH SPATIAL PROPERTIES **/

                virtual const Vector3& Offset()             const { return _modelTransform.Position(); }
                /// <summary> Gets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual const Vector3& Orientation()        const { return _worldTransform.Orientation(); }
                /// <summary> Gets the position of the entity in 3D world coordinates. </summary>
                virtual const Vector3& Position()           const { return _worldTransform.Position(); }
                /// <summary> Gets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual const Vector3& Scale()              const { return _worldTransform.Scale(); }
                virtual const Vector3& Size()               const { return _modelTransform.Scale(); }
		        

                virtual Entity3D& Offset(const Vector3& value)
                {
                    _modelTransform.Position(value);
                    return *this;
                }
                virtual Entity3D& Offset(float x, float y, float z)             { return Offset(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual Entity3D& Orientation(const Vector3& value)
                {
                    _worldTransform.Orientation(value); 
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual Entity3D& Orientation(float p, float y, float r)        { return Orientation(Vector3(p, y, r)); }
                /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Entity3D& Position(const Vector3& p)
                {
                    _worldTransform.Position(p);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Entity3D& Position(float x, float y, float z = 0.0f)    { return Position(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual Entity3D& Scale(const Vector3& s)
                {
                    _worldTransform.Scale(s);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual Entity3D& Scale(float x, float y, float z = 1.0f)       { return Scale(Vector3(x, y, z)); }
                virtual Entity3D& Size(const Vector3& value)
                {
                    _modelTransform.Scale(value);
                    return *this;
                }
                virtual Entity3D& Size(float x, float y, float z)
                {
                    return Size(Vector3(x, y, z));
                }




                /** MATERIAL PROPERTIES **/
                /// <summary> Gets a reference to the primary color of the entity. </summary>
                virtual const Color4& PrimaryColor()                    const { return _material.PrimaryColor(); }
                /// <summary> Gets a reference to the secondary color of the entity. </summary>
                virtual const Color4& SecondaryColor()                  const { return _material.SecondaryColor(); }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture3D* Texture()                      const { return _material.Texture(); }

                /// <summary> Sets the primary color of the entity. </summary>
                virtual Entity3D& PrimaryColor(const Color4& value)         { _material.PrimaryColor(value); return *this; }
                /// <summary> Sets the secondary color of the entity. </summary>
                virtual Entity3D& SecondaryColor(const Color4& value)       { _material.SecondaryColor(value); return *this; }
                /// <summary> Sets the texture to be used when rendering the entity (NOT YET IMPLEMENTED). </summary>
                virtual Entity3D& Texture(const Texture3D* value)           { _material.Texture(value); return *this; }


                
                /** RENDERABLE INTERFACE PROPERTIES **/

                virtual const List<IRenderable3D<T>*>& Components()     const override { return _components; }

                virtual const Geometry3D& Geometry()                    const override { return _geometry; }
                /// <summary> Gets whether this entity is visible in the rendered world. </summary>
                virtual bool IsVisible()                                const override { return _isVisible; }

                virtual const Material3D& Material()                    const override { return _material; }
                /// <summary> Gets a transformation data structure representing the orientation, position, and scaling of the model. </summary>
                /// <summary> Gets a reference to the model transformation matrix of the entity. </summary>
                /// <remarks>
                ///     The model matrix represents an additional affine transformation that takes place before the world transform 
                ///     is applied to the <see cref="Points"/> of any geometry. It defines the offset, size, and rotation of an entity 
                ///     in 3D model space.
                /// </remarks>
                virtual const Transform& ModelTransform()               const override { return _modelTransform; }
                /// <summary> Gets a transformation data structure representing the orientation, position, and scaling of 3D geometric shape. </summary>
                /// <summary> Gets a reference to the world transformation matrix of an entity. </summary>
                /// <remarks>
                ///     The world transform defines the position, scale, and orientation of an entity in 3D space. It is typically 
                ///     used to apply the rotation, scaling, and translation operations that place the geometry of an entity 
                ///     (defined by the <see cref="Points"/> method) into its correct position in a three-dimensional environment 
                ///     called 'world' space.
                /// </remarks>
                virtual const Transform& WorldTransform()               const override { return _worldTransform; }


                virtual Entity3D& Geometry(const Geometry3D& value)    { _geometry = value; return *this; }
                /// <summary> Sets whether the entity is visible in a rendered scene. </summary>
                virtual Entity3D& IsVisible(bool value)                { _isVisible = value; return *this; }
                virtual Entity3D& Material(const Material3D& value)    { _material = value; return *this; }



                /** DESTRUCTOR **/
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }




                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Entity3D& Rotate(const Vector3& value)           //override
                {
                    _worldTransform.Rotate(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Entity3D& Rotate(float x, float y, float z) { return Rotate(Vector3(x, y, z)); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Entity3D& Translate(const Vector3& value)        //override
                {
                    _worldTransform.Translate(value);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Entity3D& Translate(float x, float y, float z) { return Translate(Vector3(x, y, z)); }

            protected:

                /** PROPERTY DATA **/
                List<IRenderable3D<T>*> _components;



                /** CONSTRUCTOR **/
                Entity3D() { }

                Entity3D(const Geometry3D& geometry) :
                    _geometry(geometry),
                    _isVisible(true)
                {

                }

                /// <summary> Constructs a new 3D renderable entity composed of white triangles. </summary>
                /// <param name="points"> The array of points that define the geometry of this entity. </param>
		        //Entity3D(const Vector<T>& points) :
          //          Entity3D(points, Vector<uint>(0))
		        //{

		        //}
		        /// <summary> Constructs a new 3D renderable entity. </summary>
                /// <param name="color"> The base color of this entity's geometry. </param>
                /// <param name="topology"> The type of primitive that the vertices of this entity define. </param>
                /// <param name="points"> The array of points that define the geometry of this entity. </param>
          //      Entity3D(const Color4& color, VertexTopologies topology, const Vector<T>& points, const Vector<uint>& indices) :
          //          _isVisible(true)
		        //{
          //          _material.PrimaryColor(color);
		        //}






            private:
                
                /** PROPERTY DATA **/
                Geometry3D      _geometry;
                bool            _isVisible;
                Material3D      _material;
                Transform       _modelTransform;
                Transform       _worldTransform;

        };
    }
}
