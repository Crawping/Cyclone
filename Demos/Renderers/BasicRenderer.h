/* CHANGELOG
 * Written by Josh Grooms on 20160825
 */

#pragma once
#include "RendererAPI.h"
#include "TypeDefinitions.h"
#include <string>


/** FORWARD DECLARATIONS **/
namespace Cyclone
{
    namespace OpenGL
    {
        class Scene3D;
        class ShaderPipeline;
    }
    namespace Platform
    {
        class GPU;
        class Window3D;
    }
}



namespace Renderers
{
    using namespace Cyclone::OpenGL;
    using namespace Cyclone::Platform;
    using namespace Cyclone::Utilities;

    class BasicRenderer
    {
        public:
            RendererAPI virtual ~BasicRenderer();

            RendererAPI virtual void Execute();


        protected:
            bool                CanContinue;
            GPU*                Renderer;
            ShaderPipeline*     RenderPipeline;
            Scene3D*            RenderScene;
            Window3D*           RenderWindow;


            RendererAPI BasicRenderer(const string& title);
            

            RendererAPI virtual void BreakEventLoop()           { CanContinue = false; }
            RendererAPI virtual void CreateSceneResources()     { }
            RendererAPI virtual void CreateSizedResources();
    };

}