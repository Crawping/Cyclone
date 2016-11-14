/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "SVGAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include "Interfaces/IRenderStage.h"
#include <set>


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        class DrawBuffer2D;

        struct RenderStage2D : public IRenderStage
        {
            public:

                virtual const IGraphicsBuffer* Data()           const override { return (IGraphicsBuffer*)_data; }
                virtual const GraphicsSettings& Settings()      const override { return *_settings; }
                virtual VertexTopologies Topology()             const override { return VertexTopologies::Path; }

                SVGAPI RenderStage2D(const DrawBuffer2D* data, const GraphicsSettings* settings);

                SVGAPI void Render() override;


            protected:

                SVGAPI int GetResourceID(const string& name)            const;
                SVGAPI int GetUniformID(const string& name)             const;
                SVGAPI void SetResource(int id, const Color4& value)    const;
                SVGAPI void SetUniform(int id, const Color4& value)     const;
                SVGAPI void SetUniform(int id, int value)               const;


            private:
                
                const DrawBuffer2D*             _data;
                const GraphicsSettings*         _settings;

                const std::set< const IRenderable2D<float>* >* Entities;
        };
    }
}
