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
        struct RenderStage2D : public IRenderStage
        {
            public:

                virtual const IGraphicsBuffer* Data()           const override { return _data; }
                virtual const GraphicsSettings* Settings()      const override { return _settings; }
                virtual VertexTopologies Topology()             const override { return VertexTopologies::Path; }

                RenderStage2D(const IGraphicsBuffer* data, const GraphicsSettings* settings) : 
                    _data(data),
                    _settings(settings)
                {

                }

                SVGAPI void Render() override;


            private:
                
                const IGraphicsBuffer*  _data;
                const GraphicsSettings* _settings;

        };
    }
}
