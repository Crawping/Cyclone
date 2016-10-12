/* CHANGELOG 
 * Written by Josh Grooms on 20161012
 */

#pragma once
#include "SVGAPI.h"
#include "Buffers/UniformBuffer.h"
#include "Imaging/Color4.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }
    namespace SVG
    {
        class DrawBuffer2D : public IGraphicsBuffer
        {
            public:


                SVGAPI void Bind(int slot = 0) const override;
                SVGAPI void BindEntity(int slot = 0) const override;
                SVGAPI void BindResources() const override;

            private:


                UniformBuffer<Color4> FillColors;
                UniformBuffer<Color4> StrokeColors;


        };
    }
}
