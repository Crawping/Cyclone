/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#pragma once
#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "WindowEvents.h"

#include "Geometry/Scene3D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Spatial/Camera.h"
#include "Spatial/Transform.h"



namespace Renderers
{
    class AdvancedRenderer : public BasicRenderer
    {
        public:

            /** APPLICATION UTILITIES **/
            RendererAPI void Execute() override;

        protected:

            bool            IsFreeLookEnabled;
            float           MoveSpeed;
            Vector2         PointerPosition;
            Vector3         WalkingDirection;

            
            /** CONSTRUCTOR **/
            RendererAPI AdvancedRenderer(const Area& displayArea, const string& title, int nsamples = 4);



            /** INITIALIZATION UTILITIES **/
            RendererAPI virtual void CreateRenderTarget() override;

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



