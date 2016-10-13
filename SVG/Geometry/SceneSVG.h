/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "GraphicsSettings.h"
#include "SVGAPI.h"

#include "Buffers/UniformBuffer.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include <set>


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {

        class SceneSVG : public IRenderableScene
        {
            public:

                SVGAPI List<IRenderStage*> Stages() const override;

                SceneSVG& Pipeline(GraphicsPipeline* value) { _settings.Pipeline = value; return *this; }
                SceneSVG& Target(FrameBuffer* value) { _settings.Target = value; return *this; }


                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI SceneSVG();
                SVGAPI ~SceneSVG();


                SVGAPI void Add(const IRenderable2D<float>& entity);
                SVGAPI void Remove(const IRenderable2D<float>& entity);
                SVGAPI void Update() override;


            private:
                
                GraphicsSettings    _settings;


                std::set< const IRenderable2D<float>* >     Entities;

                List<IRenderStage*> Stages2D;

                UniformBuffer<Color4> Colors;

        };
    }
}
