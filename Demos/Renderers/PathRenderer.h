/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "AdvancedRenderer.h"
#include "Geometry/Scene2D.h"



namespace Renderers
{
    namespace { using namespace Cyclone::SVG; }
    class PathRenderer : public AdvancedRenderer
    {
        public:

            RendererAPI ~PathRenderer();

        protected:

            Scene2D*        PathScene;
            ShaderPipeline* PipelineSVG;



            /** CONSTRUCTOR **/
            RendererAPI PathRenderer(const Area& displayArea, const string& title);



            /** INITIALIZATION UTILITIES **/
            RendererAPI virtual void CreateSceneResources() override;
            RendererAPI virtual void CreateShaderPipeline() override;



            /** RENDERING UTILITIES **/
            RendererAPI virtual void Render() override;
            RendererAPI virtual void UpdateScene() override;

    };
}
