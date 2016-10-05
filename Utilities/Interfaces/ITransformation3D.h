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
        class ITransformation3D
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
                virtual ITransformation3D& Orientation(const Vector3& value)          = 0;
                /// <summary> Sets the (x, y, z) translation components of the transformation. </summary>
                virtual ITransformation3D& Position(const Vector3& value)             = 0;
                /// <summary> Sets the (x, y, z) scaling components of the transformation. </summary>
                virtual ITransformation3D& Scale(const Vector3& value)                = 0;



                /** DESTRUCTOR**/
                virtual ~ITransformation3D() { }



                /** UTILITIES**/
                /// <summary> Sets the (x, y, z) translation components of the transformation relative to their current values. </summary>
                virtual ITransformation3D& Translate(const Vector3& translation)      = 0;
                /// <summary> Sets the (x, y, z) rotation angles of the transformation relative to their current values. </summary>
                virtual ITransformation3D& Rotate(const Vector3& rotation)            = 0;
                /// <summary> Converts the transformation data structure into an equivalent 4x4 transformation matrix. </summary>
                virtual const Matrix4x4& ToMatrix4x4()                          const = 0;

        };
    }
}
