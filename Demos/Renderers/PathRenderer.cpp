#include "EnumerationsSVG.h"
#include "NVPR.h"
#include "PathRenderer.h"



namespace Renderers
{

    /** CONSTRUCTOR **/
    PathRenderer::PathRenderer(const Area& displayArea, const string& title) :
        AdvancedRenderer(displayArea, title, 4),
        PathScene(nullptr),
        PipelineSVG(nullptr)
    {
        IsFreeLookEnabled = false;

        nvPathStencilDepthOffset(-0.05f, -1);
        nvPathCoverDepthFunc(GL_ALWAYS);
    }
    PathRenderer::~PathRenderer()
    {
        if (PathScene) { delete PathScene; }
    }


    /** INITIALIZATION UTILITIES **/
    void PathRenderer::CreateSceneResources()
    {
        AdvancedRenderer::CreateSceneResources();

        PathScene = new Scene2D();
        PathScene->Pipeline(PipelineSVG)
            .Projection(&Projection)
            .Target(RenderTarget)
            .View(&View);
    }
    void PathRenderer::CreateShaderPipeline()
    {
        AdvancedRenderer::CreateShaderPipeline();
        PipelineSVG = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
    }



    /** RENDERING UTILITIES **/
    void PathRenderer::Render()
    {
        AdvancedRenderer::Render();
        if (PathScene)
        {
            Renderer->Scene(PathScene);
            Renderer->Update();
            Renderer->Execute();
        }
    }
    void PathRenderer::UpdateScene()
    {
        const Matrix4x4& projection = Projection.ToMatrix4x4();
        const Matrix4x4& view = View.ToMatrix4x4();

        nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());

        AdvancedRenderer::UpdateScene();
    }

}
