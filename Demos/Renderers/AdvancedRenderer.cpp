#include "AdvancedRenderer.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"



namespace Renderers
{

    AdvancedRenderer::AdvancedRenderer(const string& title) :
        BasicRenderer(title),
        MoveSpeed(16.0f)
    {

    }


    void AdvancedRenderer::Execute()
    {
        while (CanContinue())
        {
            RenderWindow->ProcessEvent();
            Renderer->Clear(ClearColor);

            UpdateScene();
            Render();
            Present();
        }
    }



    void AdvancedRenderer::CreateRenderTarget()
    {
        if (RenderTarget)
            delete RenderTarget;

        RenderTarget = new FrameBuffer(RenderWindow->ClientArea().Scale(), TextureFormats::Byte4, TextureFormats::DepthStencil);
        Renderer->RenderTarget(RenderTarget);
    }
    void AdvancedRenderer::CreateRenderingWindow()
    {
        BasicRenderer::CreateRenderingWindow();

        RenderWindow->IsTrackingKeyRepeat(false);
        RenderWindow->OnPointerMotion.Register(this, &AdvancedRenderer::ProcessPointerMotion);
        RenderWindow->OnKeyPress.Register(this, &AdvancedRenderer::ProcessKeyPress);
        RenderWindow->OnKeyRelease.Register(this, &AdvancedRenderer::ProcessKeyRelease);
    }
    void AdvancedRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/BlinnPhong.vsl", "../Renderers/Shaders/BlinnPhong.psl");
        Renderer->RenderPipeline(RenderPipeline);
    }
    

    void AdvancedRenderer::Render()
    {
        Renderer->Execute();
    }
    void AdvancedRenderer::Present()
    {
        Renderer->Present();
    }
    void AdvancedRenderer::UpdateScene()
    {
        if (WalkingDirection != Vector3::Zero)
        {
            Vector3 dir = WalkingDirection;
            View.Translate(dir.Normalize() * MoveSpeed);
            Renderer->View(View);
        }

        BasicRenderer::UpdateScene();
    }

    void AdvancedRenderer::ProcessKeyPress(const KeyboardEvent& evt)
    {
        Vector3 dir;
        if (evt.Key == KeyboardKeys::A)
            dir = View.Left();
        else if (evt.Key == KeyboardKeys::D)
            dir = View.Right();
        else if (evt.Key == KeyboardKeys::S)
            dir = View.Backward();
        else if (evt.Key == KeyboardKeys::W)
            dir = View.Forward();

        dir.Y = 0.0f;

        if (evt.Key == KeyboardKeys::Shift)
            dir = -Vector3::UnitY;
        else if (evt.Key == KeyboardKeys::Space)
            dir = Vector3::UnitY;

        WalkingDirection += dir;

        if (evt.Key == KeyboardKeys::F1)
            CreateTransformations();
        else if (evt.Key == KeyboardKeys::F2)
            return;
    }
    void AdvancedRenderer::ProcessKeyRelease(const KeyboardEvent& evt)
    {
        if (evt.State.Count() == 0)
        {
            WalkingDirection = Vector3::Zero;
            return;
        }

        Vector3 dir;
        if (evt.Key == KeyboardKeys::A)
            dir = View.Left();
        else if (evt.Key == KeyboardKeys::D)
            dir = View.Right();
        else if (evt.Key == KeyboardKeys::S)
            dir = View.Backward();
        else if (evt.Key == KeyboardKeys::W)
            dir = View.Forward();

        dir.Y = 0.0f;

        if (evt.Key == KeyboardKeys::Shift)
            dir = -Vector3::UnitY;
        else if (evt.Key == KeyboardKeys::Space)
            dir = Vector3::UnitY;

        WalkingDirection -= dir;
    }
    void AdvancedRenderer::ProcessPointerMotion(const PointerMotionEvent& evt)
    {
        float pitch = (evt.Delta.Y * Constants::Pi / RenderWindow->ClientArea().Height);
        float yaw = evt.Delta.X * Constants::TwoPi * 2.0f / RenderWindow->ClientArea().Width;
        View.Rotate(Vector3(pitch, yaw, 0.0f));
        Renderer->View(View);
    }

}