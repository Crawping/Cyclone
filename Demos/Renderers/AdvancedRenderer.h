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


            /** APPLICATION UTILITIES **/
            RendererAPI void Execute() override;

        protected:

            float           MoveSpeed;
            Vector3         WalkingDirection;

            
            /** CONSTRUCTOR **/
            RendererAPI AdvancedRenderer(const string& title);



            /** INITIALIZATION UTILITIES **/
            RendererAPI virtual void CreateRenderTarget() override;

            RendererAPI virtual void CreateRenderingWindow() override;

            RendererAPI virtual void CreateShaderPipeline() override;



            /** EVENT HANDLING UTILITIES **/
            RendererAPI virtual void ProcessKeyPress(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessKeyRelease(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessPointerMotion(const PointerMotionEvent& evt);



            /** RENDERING UTILITIES **/
            RendererAPI virtual void Render();

            RendererAPI virtual void Present();

            RendererAPI virtual void UpdateScene() override;

    };
}



