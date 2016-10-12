/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "SVGAPI.h"
#include "Interfaces/IRenderable.h"



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


            //private:
                

        };
    }
}
