/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "SVGAPI.h"
#include "Buffers/UniformBuffer.h"
//#include "Interfaces/IRenderable.h"
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


                SVGAPI SceneSVG();
                SVGAPI ~SceneSVG();


                SVGAPI void Add(const IRenderable2D<float>& entity);
                SVGAPI void Remove(const IRenderable2D<float>& entity);

                SVGAPI void Update();


            private:
                
                //List<IRenderable2D<float>*>     Entities;
                std::set< const IRenderable2D<float>* >     Entities;

                List<IRenderStage*> Stages2D;

                UniformBuffer<Color4> FillColors;
                UniformBuffer<Color4> StrokeColors;

        };
    }
}
