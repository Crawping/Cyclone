/* CHANGELOG
 * Written by Josh Grooms on 20161204
 */

#pragma once
#include "GL/OpenGLAPI.h" 
#include "Imaging/Color4.h"
#include "Interfaces/IMaterial.h"


namespace Cyclone
{
    namespace OpenGL
    {

        struct MaterialData
        {
            /// <summary> The base color of an entity. </summary>
            Color4      PrimaryColor;
            Color4      SecondaryColor;

            constexpr bool operator ==(const MaterialData& other) const
            {
                return (PrimaryColor == other.PrimaryColor) && (SecondaryColor == other.SecondaryColor);
            }
        };


        class Material3D : public IMaterial
        {
            
            private:
                
                /** PROPERTY DATA **/
                MaterialData        _data;
                const Texture3D*    _texture;

            public:

                /** PROPERTIES **/
                const MaterialData& Data()                          const override { return _data; }
                /// <summary> Gets the primary color of the material. </summary>
                const Color4& PrimaryColor()                        const override { return _data.PrimaryColor; }
                /// <summary> Gets the secondary color of the material. </summary>
                const Color4& SecondaryColor()                      const override { return _data.SecondaryColor; }
                /// <summary> Gets a pointer to the texture of a material. </summary>
                const Texture3D* Texture()                          const override { return _texture; }

                /// <summary> Sets the primary color of the material. </summary>
                Material3D& PrimaryColor(const Color4& value)       { _data.PrimaryColor = value; return *this; }
                /// <summary> Sets the secondary color of the material. </summary>
                Material3D& SecondaryColor(const Color4& value)     { _data.SecondaryColor = value; return *this; }
                /// <summary> Sets the texture of a material. </summary>
                Material3D& Texture(const Texture3D* value)         { _texture = value; return *this; }



                /** CONSTRUCTOR **/
                Material3D() :
                    _texture(nullptr)
                {

                }

        };
    }
}
