#include "AdvancedRenderer.h"
#include "Console.h"
#include "GPU.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"



namespace Renderers
{

	/** CONSTRUCTOR **/
    AdvancedRenderer::AdvancedRenderer(const Area& displayArea, const string& title, uint nsamples) :
        BasicRenderer(displayArea, title, nsamples),
        IsFreeLookEnabled(true),
        MoveSpeed(16.0f)
    {
		RenderWindow->IsTrackingKeyRepeat(false);
		RenderWindow->OnPointerMotion.Register(this, &AdvancedRenderer::ProcessPointerMotion);
		RenderWindow->OnKeyPress.Register(this, &AdvancedRenderer::ProcessKeyPress);
		RenderWindow->OnKeyRelease.Register(this, &AdvancedRenderer::ProcessKeyRelease);
    }



	/** PROTECTED UTILITIES **/
    void AdvancedRenderer::CreateShaderPipeline()
    {
        RenderPipeline = new ShaderPipeline("../Renderers/Shaders/BlinnPhong.vsl", "../Renderers/Shaders/BlinnPhong.psl");
    }    
    void AdvancedRenderer::UpdateScene()
    {
        if (WalkingDirection != Vector3::Zero)
        {
            Vector3 dir = WalkingDirection;
            View.Translate(dir.Normalize() * MoveSpeed);
        }

        BasicRenderer::UpdateScene();
    }
    void AdvancedRenderer::UpdateWalkingDirection()
    {
        WalkingDirection = Vector3::Zero;
        if (KeyboardState.Count() == 0) { return; }

        if (KeyboardState.IsPressed(KeyboardKeys::A))
            WalkingDirection += View.Left();
        if (KeyboardState.IsPressed(KeyboardKeys::D))
            WalkingDirection += View.Right();
        if (KeyboardState.IsPressed(KeyboardKeys::S))
            WalkingDirection += View.Backward();
        if (KeyboardState.IsPressed(KeyboardKeys::W))
            WalkingDirection += View.Forward();

        WalkingDirection.Y = 0.0f;

        if (KeyboardState.IsPressed(KeyboardKeys::Shift))
            WalkingDirection -= Vector3::UnitY;
        if (KeyboardState.IsPressed(KeyboardKeys::Space))
            WalkingDirection += Vector3::UnitY;
    }



    /** EVENT HANDLERS **/
    void AdvancedRenderer::ProcessKeyPress(const KeyboardEvent& evt)
    {
        KeyboardState = evt.State;
        UpdateWalkingDirection();

        if (evt.Key == KeyboardKeys::F1)
            CreateTransformations();
        else if (evt.Key == KeyboardKeys::F2)
            return;

        if (evt.Key == KeyboardKeys::Control)
            MoveSpeed /= 4.0f;
    }
    void AdvancedRenderer::ProcessKeyRelease(const KeyboardEvent& evt)
    {
        KeyboardState = evt.State;
        UpdateWalkingDirection();

        if (evt.Key == KeyboardKeys::Control)
            MoveSpeed *= 4.0f;
    }
    void AdvancedRenderer::ProcessPointerMotion(const PointerMotionEvent& evt)
    {
        PointerPosition = evt.Position;
        if (IsFreeLookEnabled)
        {
            float pitch = (evt.Delta.Y * Constants::Pi / RenderWindow->ClientArea().Height);
            float yaw = evt.Delta.X * Constants::TwoPi * 2.0f / RenderWindow->ClientArea().Width;
            View.Rotate(Vector3(pitch, yaw, 0.0f));
            Renderer->View(&View);

            UpdateWalkingDirection();
        }
    }

}