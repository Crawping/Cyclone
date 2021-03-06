#include "GL/OpenGL.h"
#include "Math/Math.h"
#include "Textures/GradientTexture.h"



namespace Cyclone
{
    namespace OpenGL
    {


        GradientTexture::GradientTexture(uint ncolors, const ColorGradient& colors) : 
            Texture3D(Vector4(Math::Max(ncolors, 2.0f), 1.0f, 1.0f, 4.0f), TextureFormats::Float4, TextureTargets::Texture2D),
            _gradient(colors)
        {

        }



        void GradientTexture::Update()
        {
            if (!NeedsUpdate()) { return; }
            Texture3D::Update();

            Vector<Color4> gradient = _gradient.ToVector(Width());
            glTextureSubImage2D
            (
                ID(), 
                0, 0, 0, 
                gradient.Count(), Height(), 
                Format().ToBaseFormat(), 
                NumericFormats::Float, 
                gradient.ToArray()
            );
        }
    }
}