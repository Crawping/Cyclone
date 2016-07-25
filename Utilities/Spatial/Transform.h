/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Volume;


        struct UtilitiesAPI Transform
        {
            public:
                /** PROPERTIES **/
                /// <summary> Gets the translation along the x-axis. </summary>
                float X()                                       const { return _position.X; }
                /// <summary> Gets the translation along the y-axis. </summary>
                float Y()                                       const { return _position.Y; }
                /// <summary> Gets the translation along the z-axis. </summary>
                float Z()                                       const { return _position.Z; }

                /// <summary> Sets the translation along the x-axis. </summary>
                Transform& X(float x)                                 { UpdateFlag(_position.X != x); _position.X = x; return *this; }
                /// <summary> Sets the translation along the y-axis. </summary>
                Transform& Y(float y)                                 { UpdateFlag(_position.Y != y); _position.Y = y; return *this; }
                /// <summary> Sets the translation along the z-axis. </summary>
                Transform& Z(float z)                                 { UpdateFlag(_position.Z != z); _position.Z = z; return *this; }

                /// <summary> Gets the (x, y, z) translation components of the transformation matrix. </summary>
                const Vector3& Position()                       const { return _position; }
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix. </summary>
                Transform& Position(const Vector3& p)                 { UpdateFlag(_position != p); _position = p; return *this; }
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix. </summary>
                Transform& Position(float x, float y, float z)        { return Position(Vector3(x, y, z)); }

                /// <summary> Gets the scaling factor along the x-axis. </summary>
                float ScaleX()                                  const { return _size.X; }
                /// <summary> Gets the scaling factor along the y-axis. </summary>
                float ScaleY()                                  const { return _size.Y; }
                /// <summary> Gets the scaling factor along the z-axis. </summary>
                float ScaleZ()                                  const { return _size.Z; }

                /// <summary> Sets the x-axis scaling component of the transformation matrix. </summary>
                Transform& ScaleX(float x)                            { UpdateFlag(_size.X != x); _size.X = x; return *this; }
                /// <summary> Sets the y-axis scaling component of the transformation matrix. </summary>
                Transform& ScaleY(float y)                            { UpdateFlag(_size.Y != y); _size.Y = y; return *this; }
                /// <summary> Sets the z-axis scaling component of the transformation matrix. </summary>
                Transform& ScaleZ(float z)                            { UpdateFlag(_size.Z != z); _size.Z = z; return *this; }

                /// <summary> Gets the (x, y, z) scaling components of the transformation matrix. </summary>
                const Vector3& Scale()                          const { return _size; }
                /// <summary> Sets the (x, y, z) scaling components of the transformation matrix. </summary>
                Transform& Scale(const Vector3& s)                    { UpdateFlag(_size != s); _size = s; return *this; }
                /// <summary> Sets the (x, y, z) scaling components of the transformation matrix. </summary>
                Transform& Scale(float x, float y, float z)           { return Scale(Vector3(x, y, z)); }



                /** CONSTRUCTORS **/
                /// <summary> Constructs a default transformation data structure representing a 4x4 identity matrix. </summary>
                Transform();
                /// <summary> Constructs a new transformation data structure that is a deep copy of another one. </summary>
                Transform(const Transform& other);
                /// <summary> Constructs a transformation data structure by copying an existing 4x4 transformation matrix. </summary>
                Transform(const float* m);
                /// <summary> Constructs a transformation matrix representing translation, rotation, and scaling in 3D space. </summary>
                /// <param name="position"> A three-element vector containing the desired translations along the X, Y, and Z axes. </param>
                /// <param name="size">
                ///     A three-element vector containing the desired scaling along the X, Y, and Z axes.
                ///     DEFAULT: Vector3(1.0f, 1.0f, 1.0f)
                /// </param>
                /// <param name="rotation">
                ///     A three-element vector containing the desired rotations about the X, Y, and Z axes.
                ///     DEFAULT: Vector3(0.0f, 0.0f, 0.0f)
                /// </param>
                /// <returns>
                ///     A new data structure representing a transformation matrix that can be multiplied by a set of
                ///     coordinates to translate, rotate, and scale them in 3D space.
                /// </returns>
                Transform(const Vector3& position, const Vector3& size = Vector3::One, const Vector3& angles = Vector3::Zero);



                /** STATIC CONSTRUCTORS **/
                /* PERSPECTIVEPROJECTION - Constructs a right-handed perspective projection transformation matrix.
                 *
                 *      SYNTAX:
                 *          T = Transform::PerspectiveProjection(displayVolume)
                 *
                 *      OUTPUT:
                 *          T:                  Transform
                 *                              A new transformation matrix that can be used to convert camera or view space
                 *                              coordinates into clip space. This transform assumes that the view-space follows a
                 *                              right-handed coordinate system.
                 *
                 *      INPUT:
                 *           displayVolume:     const Volume&
                 *                              The rectangular prism defining the volume of camera space that is visible on the
                 *                              screen.
                 */
                
                /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                static Transform PerspectiveProjection(const Volume& displayVolume);
                /* PERSPECTIVEPROJECTION - Constructs a right-handed perspective projection transformation matrix.
                 *
                 *      SYNTAX:
                 *          T = Transform::PerspectiveProjection(fov, aspect, znear, zfar);
                 *
                 *      OUTPUT:
                 *          T:          Tranform
                 *                      A new transformation matrix that can be used to convert camera- or view-space coordinates
                 *                      into clip space. This transform assumes that the view-space follows a right-handed coordinate
                 *                      system.
                 *
                 *      INPUTS:
                 *          fov:        float
                 *                      The vertical field of view, which is the angle (in degrees, not radians, here) subtended by
                 *                      the height of the visible rendering space.
                 *
                 *          aspect:     float
                 *                      The aspect ratio of the visible rendering space. This should be the value (WIDTH / HEIGHT),
                 *                      where WIDTH is the horizontal size of the space and HEIGHT is its vertical size. Units are
                 *                      irrelevant as long as they're consistent.
                 *
                 *          znear:      float
                 *                      The desired position of the clipping plane closest to the camera in view-space.
                 *
                 *          zfar:       float
                 *                      The desired position of the clipping plane furthest from the camera in view-space.
                 */
                 /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                static Transform PerspectiveProjection(float fov, float aspect, float znear, float zfar);
                static Transform Rotation(const Vector3& angles);
                static Transform Rotation(float roll, float pitch, float yaw);
                static Transform Scaling(const Vector3& size);
                static Transform Scaling(float x, float y, float z);
                static Transform Translation(const Vector3& position);
                static Transform Translation(float x, float y, float z);



                /** UTILITIES **/
                /// <summary> Generates a human-readable string detailing the current internal state of this data structure. </summary>
                string Report() const;
                /// <summary> Converts a transformation data structure into a native vector of values. </summary>
                const float* ToArray()                          const { UpdateState(); return State.ToArray(); }
                /// <summary> Sets the translation components of the transformation matrix relative to their current values. </summary>
                Transform& Translate(const Vector3& t)                { return Position(_position + t); }
                /// <summary> Sets the translation components of the transformation matrix relative to their current values. </summary>
                Transform& Translate(float x, float y, float z)       { return Translate(Vector3(x, y, z)); }



                /** OPERATORS **/
                bool operator ==(const Transform& other)        const;
                bool operator !=(const Transform& other)        const { return !(*this == other); }



            private:

                /** PRIVATE PROPERTIES **/
                /// <summary> Protects the update flag from being changed to 'false' in the time between matrix recalculations. </summary>
                void UpdateFlag(bool condition)                 const { _updateFlag = _updateFlag ? true : condition; }



                /** PROPERTY DATA **/
                Vector3         _position;
                Vector3         _rotation;
                Vector3         _size;
                mutable bool    _updateFlag;



                /** PRIVATE DATA **/
                /* STATE - A 4x4 affine transformation matrix representing translation and scaling operations.
                 *
                 *      This matrix is a combination of translation and scaling parameters that represents the current state of a
                 *      linear transformation. It is meant to be interpretted as a typical 4x4 transformation matrix, but is actually
                 *      stored and addressed as a flattened vector of values (in column-major format).
                 */
                mutable Matrix4x4 State;



                /** PRIVATE UTILITIES **/
                void UpdateState() const;
        };


        /// <summary> Performs matrix multiplication for two 4x4 transformation matrices. </summary>
        Transform operator *(Transform left, Transform right);
    }
}