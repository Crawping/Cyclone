/* CHANGELOG
 * Written by Josh Grooms on 20160924
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        struct Matrix4x4;
        struct Vector3;


        class ITransformation3D
        {
            public:
                virtual const Vector3& Orientation()    const = 0;
                virtual const Vector3& Position()       const = 0;
                virtual const Vector3& Scale()          const = 0;

                virtual ITransformation3D& Orientation(const Vector3& value) = 0;
                virtual ITransformation3D& Position(const Vector3& value) = 0;
                virtual ITransformation3D& Scale(const Vector3& value) = 0;


                virtual ~ITransformation3D() { }

                virtual ITransformation3D& Translate(const Vector3& translation) = 0;
                virtual ITransformation3D& Rotate(const Vector3& rotation) = 0;

                virtual const Matrix4x4& ToMatrix4x4() const = 0;
        };
    }
}
