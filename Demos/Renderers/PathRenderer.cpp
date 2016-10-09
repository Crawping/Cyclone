#include "EnumerationsSVG.h"
#include "NVPR.h"
#include "PathRenderer.h"



namespace Renderers
{

    /** CONSTRUCTOR **/
    PathRenderer::PathRenderer(const Area& displayArea, const string& title) :
        AdvancedRenderer(displayArea, title, 4)
    {
        IsFreeLookEnabled = false;

        nvPathStencilDepthOffset(-0.05f, -1);
        nvPathCoverDepthFunc(GL_ALWAYS);
    }



    /** INITIALIZATION UTILITIES **/
    void PathRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
        Renderer->Pipeline(RenderPipeline);
    }



    /** RENDERING UTILITIES **/
    void PathRenderer::UpdateScene()
    {
        const Matrix4x4& projection = Projection.ToMatrix4x4();
        const Matrix4x4& view = View.ToMatrix4x4();

        nvMatrixLoadIdentity(TransformMatrices::Projection);
        nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());

        AdvancedRenderer::UpdateScene();
    }
    
}
