/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#pragma once
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Volume;

        /// <summary> A data structure representing a 4x4 transformation matrix used to translate, scale, and rotate entities in 3D space. </summary>
        struct Transform
        {
            public:
                /** POSITIONAL PROPERTIES **/
                /// <summary> Gets the translation along the x-axis. </summary>
                virtual float X()                                       const { return _position.X; }
                /// <summary> Gets the translation along the y-axis. </summary>
                virtual float Y()                                       const { return _position.Y; }
                /// <summary> Gets the translation along the z-axis. </summary>
                virtual float Z()                                       const { return _position.Z; }

                /// <summary> Sets the translation along the x-axis. </summary>
                virtual Transform& X(float x)                                 { return Position(x, Y(), Z()); }
                /// <summary> Sets the translation along the y-axis. </summary>
                virtual Transform& Y(float y)                                 { return Position(X(), y, Z()); }
                /// <summary> Sets the translation along the z-axis. </summary>
                virtual Transform& Z(float z)                                 { return Position(X(), Y(), z); }

                /// <summary> Gets the (x, y, z) translation components of the transformation matrix. </summary>
                virtual const Vector3& Position()                       const { return _position; }
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix. </summary>
                virtual Transform& Position(const Vector3& p)                 { UpdateFlag(_position != p); _position = p; return *this; }
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix. </summary>
                virtual Transform& Position(float x, float y, float z)        { return Position(Vector3(x, y, z)); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                                   const { return _orientation.X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                                    const { return _orientation.Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                                     const { return _orientation.Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual Transform& Pitch(float p)                             { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual Transform& Roll(float r)                              { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual Transform& Yaw(float y)                               { return Orientation(Pitch(), y, Roll()); }

                /// <summary> Gets the angles of rotation about the (x, y, z) axes in radians. </summary>
                virtual const Vector3& Orientation()                    const { return _orientation; }
                /// <summary> Sets the angles of rotation about the (x, y, z) axes in radians. </summary>
                virtual Transform& Orientation(const Vector3& o)              { UpdateFlag(_orientation != o); _orientation = o; return *this; }
                /// <summary> Sets the angles of rotation about the (x, y, z) axes in radians. </summary>
                virtual Transform& Orientation(float p, float y, float r)     { return Orientation(Vector3(p, y, r)); }



                /** SCALING PROPERTIES **/
                /// <summary> Gets the scaling factor along the x-axis. </summary>
                virtual float ScaleX()                                  const { return _size.X; }
                /// <summary> Gets the scaling factor along the y-axis. </summary>
                virtual float ScaleY()                                  const { return _size.Y; }
                /// <summary> Gets the scaling factor along the z-axis. </summary>
                virtual float ScaleZ()                                  const { return _size.Z; }

                /// <summary> Sets the x-axis scaling component of the transformation matrix. </summary>
                virtual Transform& ScaleX(float x)                            { return Scale(x, ScaleY(), ScaleZ()); }
                /// <summary> Sets the y-axis scaling component of the transformation matrix. </summary>
                virtual Transform& ScaleY(float y)                            { return Scale(ScaleX(), y, ScaleZ()); }
                /// <summary> Sets the z-axis scaling component of the transformation matrix. </summary>
                virtual Transform& ScaleZ(float z)                            { return Scale(ScaleX(), ScaleY(), z); }

                /// <summary> Gets the (x, y, z) scaling components of the transformation matrix. </summary>
                virtual const Vector3& Scale()                          const { return _size; }
                /// <summary> Sets the (x, y, z) scaling components of the transformation matrix. </summary>
                virtual Transform& Scale(const Vector3& s)                    { UpdateFlag(_size != s); _size = s; return *this; }
                /// <summary> Sets the (x, y, z) scaling components of the transformation matrix. </summary>
                virtual Transform& Scale(float x, float y, float z)           { return Scale(Vector3(x, y, z)); }
                                


                /** CONSTRUCTORS **/
                /// <summary> Constructs a default transformation data structure representing a 4x4 identity matrix. </summary>
                UtilitiesAPI Transform();
                /// <summary> Constructs a new transformation data structure that is a deep copy of another one. </summary>
                /// <param name="other"> An existing transformation object whose contents are to be copied. </param>
                UtilitiesAPI Transform(const Transform& other);
                /// <summary> Constructs a transformation data structure by copying an existing 4x4 transformation matrix. </summary>
                UtilitiesAPI Transform(const float* m);
                /// <summary> Constructs a transformation matrix representing translation, rotation, and scaling in 3D space. </summary>
                /// <param name="position"> A three-element vector containing the desired translations along the (x, y, z) axes. </param>
                /// <param name="size">
                ///     A three-element vector containing the desired scaling along the (x, y, z) axes.
                ///     DEFAULT: Vector3(1.0f, 1.0f, 1.0f)
                /// </param>
                /// <param name="rotation">
                ///     A three-element vector containing the desired rotations about the (x, y, z) axes.
                ///     DEFAULT: Vector3(0.0f, 0.0f, 0.0f)
                /// </param>
                /// <returns>
                ///     A new data structure representing a transformation matrix that can be multiplied by a set of
                ///     coordinates to translate, rotate, and scale them in 3D space.
                /// </returns>
                UtilitiesAPI Transform(const Vector3& position, const Vector3& size = Vector3::One, const Vector3& angles = Vector3::Zero);



                /** STATIC CONSTRUCTORS **/
                /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                /// <param name="displayVolume"> The rectangular prism defining the volume of camera space that is visible on the screen. </param>
                /// <returns>
                ///     A new transformation matrix that can be used to convert camera or view space coordinates into clip space.
                ///     This transform assumes that the view-space follows a right-handed coordinate system.
                /// </returns>
                UtilitiesAPI static Transform PerspectiveProjection(const Volume& displayVolume);
                /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                /// <param name="fov">
                ///     The vertical field of view, which is the angle (in degrees, not radians, here) subtended by the height of
                ///     the visible rendering space.
                /// </param>
                /// <param name="aspect">
                ///     The aspect ratio of the visible rendering space. This should be the value (WIDTH / HEIGHT), where WIDTH is
                ///     the horizontal size of the space and HEIGHT is its vertical size. Units are irrelevant as long as they're
                ///     consistent.
                /// </param>
                /// <param name="znear"> The desired position of the clipping plane closest to the camera in view-space. </param>
                /// <param name="zfar"> The desired position of the clipping plane furthest from the camera in view-space. </param>
                /// <returns>
                ///     A new transformation matrix that can be used to convert camera- or view-space coordinates into clip space.
                ///     This transform assumes that the view-space follows a right-handed coordinate system.
                /// </returns>
                UtilitiesAPI static Transform PerspectiveProjection(float fov, float aspect, float znear, float zfar);
                /// <summary> Constructs a transformation matrix that can be used to rotate an entity about the three spatial axes. </summary>
                /// <param name="angles"> A three-element vector representing the desired (pitch, yaw, roll) rotations of the transform in radians. </param>
                /// <remarks> The transform constructed by this method follows the right-hand rule for rotation about any axis. </remarks>
                UtilitiesAPI static Transform Rotation(const Vector3& angles);
                /// <summary> Constructs a transformation matrix that can be used to rotate an entity about the three spatial axes. </summary>
                /// <param name="pitch"> The rotation about the x-axis in radians. </param>
                /// <param name="yaw"> The rotation about the y-axis in radians. </param>
                /// <param name="roll"> The rotation about the z-axis in radians. </param>
                /// <remarks> The transform constructed by this method follows the right-hand rule for rotation about any axis. </remarks>
                UtilitiesAPI static Transform Rotation(float pitch, float yaw, float roll);
                UtilitiesAPI static Transform Scaling(const Vector3& size);
                UtilitiesAPI static Transform Scaling(float x, float y, float z);
                UtilitiesAPI static Transform Translation(const Vector3& position);
                UtilitiesAPI static Transform Translation(float x, float y, float z);



                /** UTILITIES **/
                UtilitiesAPI Transform Inverse() const;
                UtilitiesAPI Transform& Invert();
                /// <summary> Generates a human-readable string detailing the current internal state of this data structure. </summary>
                UtilitiesAPI virtual string Report()                                const;
                /// <summary> Sets the rotation components of the transformation matrix relative to their current values. </summary>
                virtual Transform& Rotate(const Vector3& angles)                          { return Orientation(_orientation + angles); }
                /// <summary> Sets the rotation components of the transformation matrix relative to their current values. </summary>
                virtual Transform& Rotate(float p, float y, float r)                      { return Rotate(Vector3(p, y, r)); }
                /// <summary> Converts a transformation data structure into a native vector of values. </summary>
                UtilitiesAPI virtual const float* ToArray()                         const { UpdateState(); return State.ToArray(); }

                UtilitiesAPI virtual const Matrix4x4& ToMatrix4x4()                 const { UpdateState(); return State; }
                /// <summary> Sets the translation components of the transformation matrix relative to their current values. </summary>
                virtual Transform& Translate(const Vector3& t)                            { return Position(_position + t); }
                /// <summary> Sets the translation components of the transformation matrix relative to their current values. </summary>
                virtual Transform& Translate(float x, float y, float z)                   { return Translate(Vector3(x, y, z)); }



                /** OPERATORS **/
                /// <summary> Determines whether one transformation is equivalent to another. </summary>
                /// <returns> A Boolean <c>true</c> if the both transformations are identical, or <c>false</c> otherwise. </returns>
                UtilitiesAPI virtual bool operator ==(const Transform& other)       const;
                /// <summary> Determines whether one transformation is not equivalent to another. </summary>
                /// <returns> A Boolean <c>true</c> if the transformations are not identical, or <c>false</c> otherwise. </returns>
                virtual bool operator !=(const Transform& other)                    const { return !(*this == other); }
                
                virtual Vector4 operator *(const Vector4& right)                    const { return ToMatrix4x4() * right; }



            private:

                /** PRIVATE PROPERTIES **/
                /// <summary> Protects the update flag from being changed to 'false' in the time between matrix recalculations. </summary>
                void UpdateFlag(bool condition)                             const { _updateFlag = _updateFlag ? true : condition; }



                /** PROPERTY DATA **/
                Vector3         _orientation;
                Vector3         _position;
                Vector3         _size;
                mutable bool    _updateFlag;



                /** PRIVATE DATA **/
                /// <summary> A 4x4 affine transformation matrix representing translation, scaling, and rotation operations. </summary>
                /// <remarks>
                ///     This matrix is a combination of translation, scaling, and rotation parameters that represents the current state
                ///     of a linear transformation. It is meant to be interpretted as a typical 4x4 transformation matrix, but is actually
                ///     stored and addressed as a flattened vector of values (in column-major format).
                /// </remarks>
                mutable Matrix4x4 State;



                /** PRIVATE UTILITIES **/
                void UpdateState() const;
        };


        /// <summary> Performs matrix multiplication for two 4x4 transformation matrices. </summary>
        UtilitiesAPI Transform operator *(Transform left, Transform right);
    }
}
