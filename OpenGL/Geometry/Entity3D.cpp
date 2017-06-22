#include "Geometry/Entity3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** GEOMETRY PROPERTIES **/
        Entity3D& Entity3D::Geometry(Resource<Geometry3D> value)
        {
            _model->Geometry(value);
            return *this;
        }
        Entity3D& Entity3D::Orientation(const Vector3& value)
        {
            _transform.Orientation(value);
            return *this;
        }
        Entity3D& Entity3D::Position(const Vector3& value)
        {
            _transform.Position(value);
            return *this;
        }
        Entity3D& Entity3D::Scale(const Vector3& value)
        {
            _transform.Scale(value);
            return *this;
        }



        /** MATERIAL PROPERTIES **/
        Entity3D& Entity3D::Ambience(float value)
        {
            _material->Ambience(value);
            return *this;
        }
        Entity3D& Entity3D::PrimaryColor(const Color4& value)
        {
            _material->PrimaryColor(value);
            return *this;
        }
        Entity3D& Entity3D::SecondaryColor(const Color4& value)
        {
            _material->SecondaryColor(value);
            return *this;
        }
        Entity3D& Entity3D::SpecularPower(float value)
        {
            _material->SpecularPower(value);
            return *this;
        }
        Entity3D& Entity3D::Texture(Resource<ITexture> value)
        {
            _material->Texture(value);
            return *this;
        }



        /** IRENDERABLE PROPERTIES **/
        Entity3D& Entity3D::IsVisible(bool value)
        {
            _isVisible = value;
            return *this;
        }
        Entity3D& Entity3D::Material(Resource<Material3D> value)
        {
            _material = value;
            return *this;
        }
        Entity3D& Entity3D::Model(Resource<Model3D> value)
        {
            _model = value;
            return *this;
        }
        Entity3D& Entity3D::Settings(Resource<IGraphicsSettings> value)
        {
            _settings = value;
            return *this;
        }
        Entity3D& Entity3D::Transform(const Transform3D& value)
        {
            _transform = value;
            return *this;
        }

    }
}