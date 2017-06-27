/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#pragma once
#include "Interfaces/ISpatialTransform.h"
#include "Interfaces/ITransformable3D.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Volume;

        /// <summary> A data structure representing a 4x4 transformation matrix used to translate, scale, and rotate entities in 3D space. </summary>
        struct Transform3D: 
            public virtual ISpatialTransform,
            public virtual ITransformable3D
        {

            public:
                
                /** PROPERTIES **/
                /// <summary> Gets the angles of rotation about the (x, y, z) axes in radians. </summary>
                const Vector3& Orientation()                    const override { return _orientation; }
                /// <summary> Gets the (x, y, z) translation components of the transformation matrix. </summary>
                const Vector3& Position()                       const override { return _position; }
                /// <summary> Gets the (x, y, z) scaling components of the transformation matrix. </summary>
                const Vector3& Scale()                          const override { return _size; }

                /// <summary> Sets the angles of rotation about the (x, y, z) axes in radians. </summary>
                UtilitiesAPI Transform3D& Orientation(const Vector3& value)   override;
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix. </summary>
                UtilitiesAPI Transform3D& Position(const Vector3& value)      override;
                /// <summary> Sets the (x, y, z) scaling components of the transformation matrix. </summary>
                UtilitiesAPI Transform3D& Scale(const Vector3& value)         override;



                /** CONSTRUCTORS **/
                /// <summary> Constructs a default transformation data structure representing a 4x4 identity matrix. </summary>
                UtilitiesAPI Transform3D();
                /// <summary> Constructs a new transformation data structure that is a deep copy of another one. </summary>
                /// <param name="other"> An existing transformation object whose contents are to be copied. </param>
                UtilitiesAPI Transform3D(const Transform3D& other);
                /// <summary> Constructs a transformation data structure by copying an existing 4x4 transformation matrix. </summary>
                UtilitiesAPI Transform3D(const float* m);
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
                UtilitiesAPI Transform3D(const Vector3& position, const Vector3& size = Vector3::One, const Vector3& angles = Vector3::Zero);



                /** STATIC CONSTRUCTORS **/
                /// <summary> Constructs a transformation data structure by mathematically decomposing a 4x4 transformation matrix. </summary>
                /// <returns> 
                ///     A new transformation matrix whose translation, scaling, and orientation components are derived from the 
                ///     inputted matrix.
                /// </returns>
                /// <param name="transform"> An existing 4x4 transformation matrix. </param>
                /// <remarks>
                ///     Transformation matrix decomposition attempts to calculate the translation, scaling, and orientation 
                ///     components that contribute to the overall matrix formation. However, this process is inexact for a 
                ///     few reasons. Firstly, many individual transformations can be concatenated together to form a single 
                ///     transformation matrix, and decomposition is only able to resolve a single set of parameters. Secondly, 
                ///     and related to the first point, there are infinitely many ways to generate any given transformation, 
                ///     even with a single set of parameters. Therefore, while the result returned by this method will be 
                ///     mathematically equivalent to the inputted matrix, it very likely will not be identical.
                /// </remarks>
                UtilitiesAPI static Transform3D Decompose(const Matrix4x4& transform);
                /// <summary> Constructs a right-handed orthographic projection transformation matrix. </summary>
                /// <returns>
                ///     A new transformation matrix that can be used to convert camera- or view-space coordinates into clip space.
                ///     This transform assumes that the view-space follows a right-handed coordinate system.
                /// </returns>
                /// <param name="displayVolume"> The rectangular prism defining the volume of camera-space that is visible on the screen. </param>
                UtilitiesAPI static Transform3D OrthographicProjection(const Volume& displayVolume);
                /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                /// <returns>
                ///     A new transformation matrix that can be used to convert camera- or view-space coordinates into clip space.
                ///     This transform assumes that the view-space follows a right-handed coordinate system.
                /// </returns>
                /// <param name="displayVolume"> The rectangular prism defining the volume of camera-space that is visible on the screen. </param>
                UtilitiesAPI static Transform3D PerspectiveProjection(const Volume& displayVolume);
                /// <summary> Constructs a right-handed perspective projection transformation matrix. </summary>
                /// <returns>
                ///     A new transformation matrix that can be used to convert camera- or view-space coordinates into clip space.
                ///     This transform assumes that the view-space follows a right-handed coordinate system.
                /// </returns>
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
                UtilitiesAPI static Transform3D PerspectiveProjection(float fov, float aspect, float znear, float zfar);
                /// <summary> Constructs a transformation matrix that can be used to rotate an entity about the three spatial axes. </summary>
                /// <param name="angles"> A three-element vector representing the desired (pitch, yaw, roll) rotations of the transform in radians. </param>
                /// <remarks> The transform constructed by this method follows the right-hand rule for rotation about any axis. </remarks>
                UtilitiesAPI static Transform3D Rotation(const Vector3& angles);
                /// <summary> Constructs a transformation matrix that can be used to rotate an entity about the three spatial axes. </summary>
                /// <param name="pitch"> The rotation about the x-axis in radians. </param>
                /// <param name="yaw"> The rotation about the y-axis in radians. </param>
                /// <param name="roll"> The rotation about the z-axis in radians. </param>
                /// <remarks> The transform constructed by this method follows the right-hand rule for rotation about any axis. </remarks>
                UtilitiesAPI static Transform3D Rotation(float pitch, float yaw, float roll);
                /// <summary> Constructs a transformation matrix that can be used to scale an entity along the three spatial axes. </summary>
                /// <param name="size"> A three-element vector containing the desired (width, height, depth) scaling factors of the transform. </param>
                UtilitiesAPI static Transform3D Scaling(const Vector3& size);
                /// <summary> Constructs a transformation matrix that can be used to scale an entity along the three spatial axes. </summary>
                /// <param name="x"> The desired scaling factor along the x-axis. </param>
                /// <param name="y"> The desired scaling factor along the y-axis. </param>
                /// <param name="z"> The desired scaling factor along the z-axis. </param>
                UtilitiesAPI static Transform3D Scaling(float x, float y, float z);
                /// <summary> Constructs a transformation matrix that can be used to translate an entity along the three spatial axes. </summary>
                /// <param name="position"> A three-element vector containing the desired (x, y, z) translation amounts. </param>
                UtilitiesAPI static Transform3D Translation(const Vector3& position);
                /// <summary> Constructs a transformation matrix that can be used to translate an entity along the three spatial axes. </summary>
                /// <param name="x"> The desired amount of translation along the x-axis. </param>
                /// <param name="y"> The desired amount of translation along the y-axis. </param>
                /// <param name="z"> The desired amount of translation along the z-axis. </param>
                UtilitiesAPI static Transform3D Translation(float x, float y, float z);



                /** UTILITIES **/
                /// <summary> Generates a new transformation object that represents the inverse of this one. </summary>
                UtilitiesAPI Transform3D Inverse()                                  const;
                /// <summary> Generates a human-readable string detailing the current internal state of this data structure. </summary>
                UtilitiesAPI virtual string Report()                                const;
                /// <summary> Sets the rotation components of the transformation matrix relative to their current values. </summary>
                UtilitiesAPI Transform3D& Rotate(const Vector3& value)              override;
                /// <summary> Converts a transformation data structure into a native vector of values. </summary>
                UtilitiesAPI virtual const float* ToArray()                         const override; 
                /// <summary> Converts a transformation data structure into an ordinary 4x4 transformation matrix. </summary>
                /// <returns> A reference to the transformation matrix that performs the desired rotation, scaling, and translation operations. </returns>
                UtilitiesAPI virtual const Matrix4x4& ToMatrix4x4()                 const override;
                /// <summary> Sets the translation components of the transformation matrix relative to their current values. </summary>
                UtilitiesAPI Transform3D& Translate(const Vector3& value)           override;



                /** OPERATORS **/
                /// <summary> Determines whether one transformation is equivalent to another. </summary>
                /// <returns> A Boolean <c>true</c> if the both transformations are identical, or <c>false</c> otherwise. </returns>
                UtilitiesAPI virtual bool operator ==(const Transform3D& other)     const;
                /// <summary> Determines whether one transformation is not equivalent to another. </summary>
                /// <returns> A Boolean <c>true</c> if the transformations are not identical, or <c>false</c> otherwise. </returns>
                virtual bool operator !=(const Transform3D& other)                  const { return !(*this == other); }
                /// <summary> Performs matrix multiplication between a 4x4 transformation matrix and a vector. </summary>
                /// <returns> A three-element vector representing the spatially transformed input. </returns>
                /// <param name="right"> A three-element vector that serves as the right operand of the multiplication. </param>
                virtual Vector3 operator *(const Vector3& right)                    const { return Vector3(ToMatrix4x4() * Vector4(right, 1.0f)); }
                /// <summary> Performs matrix multiplication between a 4x4 transformation matrix and a vector. </summary>
                /// <returns> A four-element vector representing the spatially transformed input. </returns>
                /// <param name="right"> A four-element vector that serves as the right operand of the multiplication. </param>
                virtual Vector4 operator *(const Vector4& right)                    const { return ToMatrix4x4() * right; }
                /// <summary> Performs matrix multiplication for two 4x4 transformation matrices. </summary>
                /// <returns> A transformation object representing the combined input transformations. </returns>
                /// <param name="other"> Another 4x4 transformation matrix that serves as the right operand of the multiplication. </param>
                UtilitiesAPI virtual Transform3D operator *(const Transform3D& other)   const;



            private:

                /** PROPERTY DATA **/
                mutable bool    _needsUpdate;
                Vector3         _orientation;
                Vector3         _position;
                Vector3         _size;



                /** PRIVATE DATA **/
                /// <summary> A 4x4 affine transformation matrix representing translation, scaling, and rotation operations. </summary>
                /// <remarks>
                ///     This matrix is a combination of translation, scaling, and rotation parameters that represents the current state
                ///     of a linear transformation. It is meant to be interpretted as a typical 4x4 transformation matrix, but is actually
                ///     stored and addressed as a flattened vector of values (in column-major format).
                /// </remarks>
                mutable Matrix4x4 State;



                /** PRIVATE UTILITIES **/
                void Update() const;

        };
    }
}
