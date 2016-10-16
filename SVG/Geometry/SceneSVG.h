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

        class SceneSVG : public IRenderableScene
        {
            public:

                SVGAPI const List<IRenderStage*>& Stages()             const override;

                SceneSVG& Pipeline(GraphicsPipeline* value)     { _settings.Pipeline = value; return *this; }
                SceneSVG& Projection(ITransformation3D* value)  { _settings.Projection = value; return *this; }
                SceneSVG& Target(FrameBuffer* value)            { _settings.Target = value; return *this; }
                SceneSVG& View(ITransformation3D* value)        { _settings.View = value; return *this; }


                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI SceneSVG();
                SVGAPI ~SceneSVG();


                SVGAPI void Add(const IRenderable2D<float>& entity);
                SVGAPI void Remove(const IRenderable2D<float>& entity);
                SVGAPI void Update() override;
                SVGAPI void Update(const IRenderable2D<float>& entity);


            private:
                
                GraphicsSettings    _settings;

                DrawBuffer2D        Buffers;


                //std::set< const IRenderable2D<float>* >     Entities;

                List<IRenderStage*> Stages2D;

                //UniformBuffer<Color4> Colors;

        };
    }
}
