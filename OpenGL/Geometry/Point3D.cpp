#include "Geometry/Point3D.h"
#include "GL/OpenGL.h"
#include "Math/Math.h"



namespace Cyclone
{
    namespace OpenGL
    {
        Point3D& Point3D::Depth(float z)
        {
            glPointSize(Math::Max(Width(), Height(), z));
            Entity3D::Depth(z);
            return *this;
        }
        Point3D& Point3D::Height(float y)
        {
            glPointSize(Math::Max(Width(), y, Depth()));
            Entity3D::Height(y);
            return *this;
        }
        Point3D& Point3D::Width(float x)
        {
            glPointSize(Math::Max(x, Height(), Depth()));
            Entity3D::Width(x);
            return *this;
        }

        Point3D& Point3D::Scale(const Vector3& value)
        {
            glPointSize(Math::Max(value.X, value.Y, value.Z));
            Entity3D::Scale(value);
            return *this;
        }
        Point3D& Point3D::Scale(float x, float y, float z)
        {
            glPointSize(Math::Max(x, y, z));
            Entity3D::Scale(x, y, z);
            return *this;
        }
    }
}