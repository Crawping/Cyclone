#include "Models/Model3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        //Model3D& Model3D::Geometry(const Geometry3D& value)
        Model3D& Model3D::Geometry(Component<Geometry3D> value)
        {
            _geometry = value;
            return *this;
        }
        Model3D& Model3D::Orientation(const Vector3& value)
        {
            _transform.Orientation(value);
            return *this;
        }
        Model3D& Model3D::Position(const Vector3& value)
        {
            _transform.Position(value);
            return *this;
        }
        Model3D& Model3D::Scale(const Vector3& value)
        {
            _transform.Scale(value);
            return *this;
        }
        Model3D& Model3D::Transform(const Transform3D& value)
        {
            _transform = value;
            return *this;
        }



        /** CONSTRUCTORS **/
        Model3D::Model3D() { }
        Model3D::Model3D(Component<Geometry3D> geometry) :
            _geometry(geometry)
        {

        }

    }
}