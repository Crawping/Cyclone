/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "RenderStage.h"
#include "SVGAPI.h"


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        struct RenderStage2D : public RenderStage3D
        {
            public:

                RenderStage2D(const IGraphicsBuffer* data, const GraphicsSettings* settings) : 
                    RenderStage3D(VertexTopologies::Path, data, settings)
                {

                }

                SVGAPI void Render() override;
        };
    }
}
