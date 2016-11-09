/* CHANGELOG
 * Written by Josh Grooms on 20161109
 */

#pragma once
#include "Collections/List.h"
#include "Imaging/ColorGradient.h"
#include "Textures/Texture.h"



namespace Cyclone
{
    namespace OpenGL
    {

        struct GradientShapes : public Enumerator
        {
            enum Shapes
            {
                Linear,
                Radial,
            };

            constexpr GradientShapes(enum Shapes t = Linear) : Enumerator((int)t) { }
        };

        struct ColorStop
        {
            Color4  Color;
            float   Position;
        };

        class GradientTexture : public Texture3D
        {
            public:

                OpenGLAPI GradientTexture(const ColorGradient& colors);

                OpenGLAPI void Add(const ColorStop& color);
                OpenGLAPI void Update() override;

            protected:


            private:
                GradientShapes      _shape;
                List<ColorStop>     _stops;

        };
    }
}
