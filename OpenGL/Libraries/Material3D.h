/* CHANGELOG
 * Written by Josh Grooms on 20161204
 */

#pragma once
#include "GL/OpenGLAPI.h" 
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"


namespace Cyclone
{
    namespace OpenGL
    {
        class Material3D : public IMaterialEntity
        {
            public:

                const Color4& PrimaryColor()    const override { return _primaryColor; }
                const Color4& SecondaryColor()  const override { return _secondaryColor; }
                const Texture3D* Texture()      const override { return _texture; }

                Material3D& PrimaryColor(const Color4& value)       { _primaryColor = value; return *this; }
                Material3D& SecondaryColor(const Color4& value)     { _secondaryColor = value; return *this; }
                Material3D& Texture(const Texture3D* value)         { _texture = value; return *this; }



                Material3D() :
                    _texture(nullptr)
                {

                }






            private:
                Color4              _primaryColor;
                Color4              _secondaryColor;
                const Texture3D*    _texture;

            
        };
    }
}
