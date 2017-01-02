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

        nvPathStencilDepthOffset(-0.001f, -1.0f);
        nvPathCoverDepthFunc(GL_ALWAYS);
    }
    PathRenderer::~PathRenderer()
    {
        if (PathScene)      { delete PathScene; }
        if (PipelineSVG)    { delete PipelineSVG; }
    }


    /** INITIALIZATION UTILITIES **/
    void PathRenderer::CreateSceneResources()
    {
        AdvancedRenderer::CreateSceneResources();

        //PathScene = new Scene2D();
        PathScene = new SceneComponent2D("Path", *RenderScene);
        PathScene->
             IsStencilTestEnabled(true)
            .Pipeline(PipelineSVG)
            .Projection(&Projection)
            .Target(RenderTarget)
            .View(&View);

        RenderScene->Insert("Path", *PathScene);

    }
    void PathRenderer::CreateShaderPipeline()
    {
        AdvancedRenderer::CreateShaderPipeline();
        PipelineSVG = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
    }



    /** RENDERING UTILITIES **/
    void PathRenderer::UpdateScene()
    {
        const Matrix4x4& projection = Projection.ToMatrix4x4();
        const Matrix4x4& view = View.ToMatrix4x4();

        nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());

        AdvancedRenderer::UpdateScene();
    }

}
