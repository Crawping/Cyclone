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



namespace Cyclone
{
    namespace Renderers
    {
        class AdvancedRenderer : public BasicRenderer
        {
            protected:

                bool                IsFreeLookEnabled;
                KeyboardKeys        KeyboardState;
                float               MoveSpeed;
                Vector2             PointerPosition;
                Vector<Vector3, 2>  PointerWorldRay;
                Matrix4x4           ViewProjection;
                Matrix4x4           ViewProjectionInv;
                Vector3             WalkingDirection;

            
                /** CONSTRUCTOR **/
                RendererAPI AdvancedRenderer(const Area& displayArea, const string& title, uint nsamples = 4);



                /** INITIALIZATION UTILITIES **/
                RendererAPI virtual void CreateTransformations() override;



                /** EVENT HANDLING UTILITIES **/
                RendererAPI virtual void ProcessKeyPress(const KeyboardEvent& evt);

                RendererAPI virtual void ProcessKeyRelease(const KeyboardEvent& evt);

                RendererAPI virtual void ProcessPointerMotion(const PointerMotionEvent& evt);



                /** RENDERING UTILITIES **/
                RendererAPI virtual Vector2 CalculatePointerInWorld(float z);

                RendererAPI virtual void UpdatePointerWorldRay();

                RendererAPI virtual void UpdateScene() override;

                RendererAPI virtual void UpdateViewProjection();

                RendererAPI virtual void UpdateWalkingDirection();

        };
    }
}



