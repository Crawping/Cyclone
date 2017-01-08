/* CHANGELOG
 * Written by Josh Grooms on 20160924
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {

        /** FORWARD DECLARATIONS**/
        struct Matrix4x4;
        struct Vector3;

        /// <summary> An interface that represents a generalized 3D affine geometric transformation. </summary>
        class ISpatialTransform
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the (x, y, z) rotation angles of the transformation in radians. </summary>
                virtual const Vector3& Orientation()                            const = 0;
                /// <summary> Gets the (x, y, z) translation components of the transformation. </summary>
                virtual const Vector3& Position()                               const = 0;
                /// <summary> Gets the (x, y, z) scaling components of the transformation. </summary>
                virtual const Vector3& Scale()                                  const = 0;

                /// <summary> Sets the (x, y, z) rotation angles of the transformation in radians. </summary>
                virtual ISpatialTransform& Orientation(const Vector3& value)          = 0;
                /// <summary> Sets the (x, y, z) translation components of the transformation. </summary>
                virtual ISpatialTransform& Position(const Vector3& value)             = 0;
                /// <summary> Sets the (x, y, z) scaling components of the transformation. </summary>
                virtual ISpatialTransform& Scale(const Vector3& value)                = 0;



                /** DESTRUCTOR**/
                virtual ~ISpatialTransform() { }



                /** UTILITIES**/
                /// <summary> Sets the (x, y, z) translation components of the transformation relative to their current values. </summary>
                virtual ISpatialTransform& Translate(const Vector3& translation)      = 0;
                /// <summary> Sets the (x, y, z) rotation angles of the transformation relative to their current values. </summary>
                virtual ISpatialTransform& Rotate(const Vector3& rotation)            = 0;
                /// <summary> Converts the transformation data structure into an equivalent 4x4 transformation matrix. </summary>
                virtual const Matrix4x4& ToMatrix4x4()                          const = 0;
                /// <summary> Converts the transformation data structure into an equivalent native vector of values. </summary>
                virtual const float* ToArray()                                  const = 0;

        };
    }
}
