#include "Textures/GradientTexture.h"



namespace Cyclone
{
    namespace OpenGL
    {


        GradientTexture::GradientTexture(const ColorGradient& colors) : 
            Texture3D(Vector4(colors.Count(), 1.0f, 1.0f, 4.0f), TextureFormats::Byte4, TextureTargets::Texture1D)
        {

        }


        void GradientTexture::Add(const ColorStop& color)
        {
            _stops.Append(color);
            NeedsUpdate(true);
        }
        void GradientTexture::Update()
        {
            if (!NeedsUpdate()) { return; }


            
        }


    }
}