#include "Libraries/Material3D.h"
#include "Textures/Texture3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        Material3D& Material3D::Ambience(float value)
        {
            _data.Ambience = value;
            return *this;
        }
        Material3D& Material3D::Data(const MaterialData& value)
        {
            _data = value;
            return *this;
        }
        Material3D& Material3D::Orientation(const Vector3& value)
        {
            _transform.Orientation(value);
            return *this;
        }
        Material3D& Material3D::Position(const Vector3& value)
        {
            _transform.Position(value);
            return *this;
        }
        Material3D& Material3D::PrimaryColor(const Color4& value)
        {
            _data.PrimaryColor = value;
            return *this;
        }
        Material3D& Material3D::Scale(const Vector3& value)
        {
            _transform.Scale(value);
            return *this;
        }
        Material3D& Material3D::SecondaryColor(const Color4& value)
        {
            _data.SecondaryColor = value;
            return *this;
        }
        Material3D& Material3D::SpecularPower(float value)
        {
            _data.SpecularPower = value;
            return *this;
        }
        Material3D& Material3D::Texture(Component<ITexture> value)
        {
            _texture            = value;
            _data.IsTextured    = !value.IsNull();
            _data.Texture       = value.IsNull() ? 0 : value->Handle();
            return *this;
        }
        Material3D& Material3D::Transform(const Transform3D& value)
        {
            _transform = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        Material3D::Material3D():
            _texture("Null", nullptr)
        {

        }



        /** UTILITIES **/
        Material3D* Material3D::CreateView() const
        {
            return nullptr;
        }

    }
}