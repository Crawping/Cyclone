/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "AdvancedRenderer.h"
#include "Geometry/SceneSVG.h"



namespace Renderers
{
    namespace { using namespace Cyclone::SVG; }
    class PathRenderer : public AdvancedRenderer
    {
        public:

            RendererAPI ~PathRenderer();

        protected:

            SceneSVG* PathScene;

            /** CONSTRUCTOR **/
            RendererAPI PathRenderer(const Area& displayArea, const string& title);



            /** INITIALIZATION UTILITIES **/
            RendererAPI virtual void CreateSceneResources() override;
            RendererAPI virtual void CreateShaderPipeline() override;



            /** RENDERING UTILITIES **/
            RendererAPI virtual void UpdateScene() override;

    };
}
