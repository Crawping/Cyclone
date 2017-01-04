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

        class Material3D : public IMaterial
        {
            
            public:

                /** PROPERTIES **/
                /// <summary> Gets a structure containing all of the data needed to render the material. </summary>
                const MaterialData& Data()                          const override { return _data; }
                /// <summary> Gets the primary color of the material. </summary>
                const Color4& PrimaryColor()                        const override { return _data.PrimaryColor; }
                /// <summary> Gets the secondary color of the material. </summary>
                const Color4& SecondaryColor()                      const override { return _data.SecondaryColor; }
                /// <summary> Gets a pointer to the texture of a material. </summary>
                const Texture3D* Texture()                          const override { return _texture; }

                /// <summary> Summarily sets all of the data needed to render the material. </summary>
                Material3D& Data(const MaterialData& value)
                {
                    _data = value;
                    return *this;
                }
                /// <summary> Sets the primary color of the material. </summary>
                Material3D& PrimaryColor(const Color4& value)       
                { 
                    _data.PrimaryColor = value; 
                    return *this;
                }
                /// <summary> Sets the secondary color of the material. </summary>
                Material3D& SecondaryColor(const Color4& value)
                { 
                    _data.SecondaryColor = value;
                    return *this;
                }
                /// <summary> Sets the texture of a material. </summary>
                Material3D& Texture(const Texture3D* value)
                {
                    _texture = value;
                    return *this;
                }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new black textureless material that can be used to style renderable objects. </summary>
                Material3D() :
                    _texture(nullptr)
                {

                }

            private:
                
                /** PROPERTY DATA **/
                MaterialData        _data;
                const Texture3D*    _texture;

        };
    }
}
