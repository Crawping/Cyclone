/* CHANGELOG
 * Written by Josh Grooms on 20161228
 */

#pragma once
#include "Interfaces/ITransformable.h"
#include "Spatial/Transform.h"


namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace OpenGL
    {      

        class Transform3D : public virtual ITransformable
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
                virtual Transform3D& X(float x)                   { return Position(x, Y(), Z()); }
		        /// <summary> Sets the position of the entity along the world y-axis. </summary>
                virtual Transform3D& Y(float y)                   { return Position(X(), y, Z()); }
		        /// <summary> Sets the position of the entity along the world z-axis. </summary>
                virtual Transform3D& Z(float z)                   { return Position(X(), Y(), z); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                       const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                        const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                         const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual Transform3D& Pitch(float p)               { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual Transform3D& Roll(float r)                { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual Transform3D& Yaw(float y)                 { return Orientation(Pitch(), y, Roll()); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                       const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                      const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                       const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual Transform3D& Depth(float z)               { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual Transform3D& Height(float y)              { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual Transform3D& Width(float x)               { return Scale(x, Height(), Depth()); }


                
                /** BATCH SPATIAL PROPERTIES **/

                virtual const Vector3& Offset()             const { return _world.Position(); }
                /// <summary> Gets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual const Vector3& Orientation()        const { return _world.Orientation(); }
                /// <summary> Gets the position of the entity in 3D world coordinates. </summary>
                virtual const Vector3& Position()           const { return _world.Position(); }
                /// <summary> Gets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual const Vector3& Scale()              const { return _world.Scale(); }

                virtual const Vector3& Size()               const { return _world.Scale(); }
		        

                virtual Transform3D& Offset(const Vector3& value)
                {
                    _model.Position(value);
                    return *this;
                }
                virtual Transform3D& Offset(float x, float y, float z)             { return Offset(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual Transform3D& Orientation(const Vector3& value)
                {
                    _world.Orientation(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual Transform3D& Orientation(float p, float y, float r)        { return Orientation(Vector3(p, y, r)); }
                /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Transform3D& Position(const Vector3& p)
                {
                    _world.Position(p);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual Transform3D& Position(float x, float y, float z = 0.0f)    { return Position(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual Transform3D& Scale(const Vector3& s)
                {
                    _world.Scale(s);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual Transform3D& Scale(float x, float y, float z = 1.0f)       { return Scale(Vector3(x, y, z)); }
                virtual Transform3D& Size(const Vector3& value)
                {
                    _model.Scale(value);
                    return *this;
                }
                virtual Transform3D& Size(float x, float y, float z)
                {
                    return Size(Vector3(x, y, z));
                }


                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in model space. </summary>
                /// <remarks>
                ///     The model matrix represents an additional affine transformation that takes place before the world transform 
                ///     is applied to any geometry. It defines the offset, size, and rotation of an entity in 3D model space.
                /// </remarks>
                virtual const Transform& Model()            const override { return _model; }

                virtual const Transform& Texture()          const override { return _texture; }
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in world space. </summary>
                /// <remarks>
                ///     The world transform defines the position, scale, and orientation of an entity in 3D space. It is typically 
                ///     used to apply the rotation, scaling, and translation operations that place the geometry of an entity 
                ///     into its correct position in a three-dimensional environment called 'world' space.
                /// </remarks>
                virtual const Transform& World()            const override { return _world; }


                virtual Transform3D& Model(const Transform& value)
                {
                    _model = value;
                    return *this;
                }
                virtual Transform3D& Texture(const Transform& value)
                {
                    _texture = value;
                    return *this;
                }
                virtual Transform3D& World(const Transform& value)
                {
                    _world = value;
                    return *this;
                }



                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Transform3D& Rotate(const Vector3& value)
                {
                    _world.Rotate(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Transform3D& Rotate(float x, float y, float z) { return Rotate(Vector3(x, y, z)); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Transform3D& Translate(const Vector3& value)
                {
                    _world.Translate(value);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Transform3D& Translate(float x, float y, float z) { return Translate(Vector3(x, y, z)); }


            private:

                Transform _model;
                Transform _texture;
                Transform _world;

        };


    }
}
