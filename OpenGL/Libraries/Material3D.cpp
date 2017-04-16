#include "Libraries/Material3D.h"
#include "Textures/Texture3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        Material3D& Material3D::Data(const MaterialData& value)
        {
            _data = value;
            return *this;
        }
        Material3D& Material3D::PrimaryColor(const Color4& value)
        {
            _data.PrimaryColor = value;
            return *this;
        }
        Material3D& Material3D::SecondaryColor(const Color4& value)
        {
            _data.SecondaryColor = value;
            return *this;
        }
        Material3D& Material3D::Texture(Texture3D* value)
        {
            _texture = value;
            if (value)
                _data.Texture = value->Handle();
            return *this;
        }



        /** CONSTRUCTOR **/
        Material3D::Material3D() :
            _data{ Color4(), Color4(), 0, Vector2() },
            _texture(nullptr)
        {

        }
    }
}