/* CHANGELOG
 * Written by Josh Grooms on 20161109
 */

#pragma once
#include "Collections/List.h"
#include "Imaging/ColorGradient.h"
#include "Textures/Texture3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class GradientTexture : public Texture3D
        {
            public:

                OpenGLAPI GradientTexture(uint ncolors, const ColorGradient& colors);

                OpenGLAPI void Update() override;

            protected:


            private:
                GradientShapes      _shape;
                ColorGradient       _gradient;

        };
    }
}
