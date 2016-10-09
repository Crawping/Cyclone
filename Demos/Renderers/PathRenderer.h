/* CHANGELOG
 * Written by Josh Grooms on 20161008
 */

#pragma once
#include "AdvancedRenderer.h"



namespace Renderers
{
    class PathRenderer : public AdvancedRenderer
    {

        protected:

            /** CONSTRUCTOR **/
            RendererAPI PathRenderer(const Area& displayArea, const string& title);



            /** INITIALIZATION UTILITIES **/
            RendererAPI virtual void CreateShaderPipeline() override;



            /** RENDERING UTILITIES **/
            RendererAPI virtual void UpdateScene() override;

    };
}
