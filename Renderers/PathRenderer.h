/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "AdvancedRenderer.h"
#include "Scenes/SceneComponent2D.h"



namespace Cyclone
{
    namespace Renderers
    {
        namespace { using namespace Cyclone::SVG; }
        class PathRenderer : public AdvancedRenderer
        {
            public:

                RendererAPI ~PathRenderer();

            protected:

                SceneComponent2D*   PathScene;
                ShaderPipeline*     PipelineSVG;



                /** CONSTRUCTOR **/
                RendererAPI PathRenderer(const Area& displayArea, const string& title);



                /** INITIALIZATION UTILITIES **/
                RendererAPI virtual void CreateSceneResources() override;
                RendererAPI virtual void CreateShaderPipeline() override;



                /** RENDERING UTILITIES **/
                RendererAPI virtual void UpdateScene() override;

        };
    }
}