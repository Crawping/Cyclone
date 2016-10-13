/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "RenderStage.h"
#include "SVGAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include <set>


namespace Cyclone
{
    namespace { using namespace OpenGL; }
    namespace OpenGL
    {
        template<typename T> class UniformBuffer;
    }

    namespace SVG
    {
        struct RenderStage2D : public IRenderStage
        {
            public:

                virtual const IGraphicsBuffer* Data()           const override { return (IGraphicsBuffer*)_data; }
                virtual const GraphicsSettings* Settings()      const override { return _settings; }
                virtual VertexTopologies Topology()             const override { return VertexTopologies::Path; }

                SVGAPI RenderStage2D(const UniformBuffer<Color4>* data, const std::set< const IRenderable2D<float>* >* entities, const GraphicsSettings* settings);

                SVGAPI void Render() override;


            protected:

                SVGAPI int GetUniformID(const string& name) const;
                SVGAPI void SetUniform(const string& name, const Color4& value) const;
                SVGAPI void SetUniform(int id, int value) const;


            private:
                
                const UniformBuffer<Color4>*    _data;
                const GraphicsSettings*         _settings;

                const std::set< const IRenderable2D<float>* >* Entities;
        };
    }
}
