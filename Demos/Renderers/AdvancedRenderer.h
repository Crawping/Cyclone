/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#pragma once
#include "BasicRenderer.h"
#include "WindowEvents.h"



namespace Renderers
{
    class AdvancedRenderer : public BasicRenderer
    {
        public:

            

            RendererAPI void Execute() override;

        protected:

            float   MoveSpeed;
            Vector3 WalkingDirection;

            
            AdvancedRenderer(const string& title) :
                BasicRenderer(title),
                MoveSpeed(16.0f)
            {

            }


            RendererAPI virtual void CreateRenderTarget() override;

            RendererAPI virtual void CreateRenderingWindow() override;

            RendererAPI virtual void CreateShaderPipeline() override;

            RendererAPI virtual void ProcessKeyPress(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessKeyRelease(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessPointerMotion(const PointerMotionEvent& evt);

            RendererAPI virtual void Render();

            RendererAPI virtual void Present();

            RendererAPI virtual void UpdateScene() override;

    };
}



