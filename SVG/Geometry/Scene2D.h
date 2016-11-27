/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "GraphicsSettings.h"
#include "SVGAPI.h"

#include "Buffers/DrawBuffer2D.h"
#include "Buffers/UniformBuffer.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include <set>


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {

        class Scene2D : public IRenderableScene
        {
            public:

                SVGAPI List<IRenderStage*> Stages()                     const override;

                Scene2D& IsBlendEnabled(bool value)                     { _settings.IsBlendEnabled = value; return *this; }
                Scene2D& IsDepthTestEnabled(bool value)                 { _settings.IsDepthTestEnabled = value; return *this; }
                Scene2D& IsStencilTestEnabled(bool value)               { _settings.IsStencilTestEnabled = value; return *this; }
                Scene2D& Pipeline(GraphicsPipeline* value)              { _settings.Pipeline = value; return *this; }
                Scene2D& Projection(ITransformation3D* value)           { _settings.Projection = value; return *this; }
                Scene2D& Target(FrameBuffer* value)                     { _settings.Target = value; return *this; }
                Scene2D& View(ITransformation3D* value)                 { _settings.View = value; return *this; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI Scene2D();
                SVGAPI ~Scene2D();


                SVGAPI void Add(const IRenderable2D<float>& entity);
                SVGAPI void Remove(const IRenderable2D<float>& entity);
                SVGAPI void Update() override;
                SVGAPI void Update(const IRenderable2D<float>& entity);
                
            private:
                
                GraphicsSettings    _settings;

                DrawBuffer2D        Buffers;
                List<IRenderStage*> Stages2D;

        };
    }
}
