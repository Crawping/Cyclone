/* CHANGELOG
 * Written by Josh Grooms on 20160925
 */

#pragma once
#include "BasicRenderer.h"
#include "GPU.h"
#include "Window3D.h"
#include "WindowEvents.h"

#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Camera.h"
#include "Spatial/Transform.h"



namespace Renderers
{
    class AdvancedRenderer : public BasicRenderer
    {
        protected:

            bool            IsFreeLookEnabled;
            float           MoveSpeed;
            Vector2         PointerPosition;
            Vector3         WalkingDirection;

            
            /** CONSTRUCTOR **/
            RendererAPI AdvancedRenderer(const Area& displayArea, const string& title, uint nsamples = 4);



            /** INITIALIZATION UTILITIES **/
            /// <summary> Creates a rendering pipeline using the Blinn-Phong shader programs. </summary>
            RendererAPI virtual void CreateShaderPipeline() override;



            /** EVENT HANDLING UTILITIES **/
            RendererAPI virtual void ProcessKeyPress(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessKeyRelease(const KeyboardEvent& evt);

            RendererAPI virtual void ProcessPointerMotion(const PointerMotionEvent& evt);



            /** RENDERING UTILITIES **/

            RendererAPI virtual void UpdateScene() override;

    };
}



