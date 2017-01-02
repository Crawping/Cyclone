/* CHANGELOG
 * Written by Josh Grooms on 20161230
 */

#pragma once
#include "SVGAPI.h"
#include "Pipelines/RenderStage2D.h"
#include "Scenes/SceneComponent3D.h"


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        class SceneComponent2D : public SceneComponent
        {

            public:
                
                /** PROPERTIES **/
                SVGAPI List<IRenderStage&> Stages()             const override;



                /** CONSTRUCTOR **/
                SVGAPI SceneComponent2D(const string& name, ISceneLayer& parent);



                /** UTILITIES **/
                SVGAPI void Insert(uint index, const RenderStage2D& stage);
                SVGAPI void Insert(const IRenderable& entity)   override;
                SVGAPI void Remove(uint index);
                SVGAPI void Remove(const IRenderable& entity);
                SVGAPI void Update()                            override;
                SVGAPI void Update(const IRenderable& entity)   override;

            private:

                Set<const ResourceMapping*>     Resources;
                List<RenderStage2D>             _stages;

        };
    }
}
