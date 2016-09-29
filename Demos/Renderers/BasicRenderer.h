/* CHANGELOG
 * Written by Josh Grooms on 20160825
 */

#pragma once
#include "RendererAPI.h"
#include "TypeDefinitions.h"
#include "Imaging/Color4.h"
#include "Spatial/Area.h"
#include "Spatial/Camera.h"
#include "Spatial/Transform.h"
#include <string>



/** FORWARD DECLARATIONS **/
namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;
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
            
            /** PROPERTIES **/
            /// <summary> Gets a Boolean indicating whether the main event loop can continue processing. </summary>
            virtual bool CanContinue() const { return _canContinue; }



            /** DESTRUCTOR **/
            /// <summary> Destroys GPU- and heap-allocated resources held by the rendering engine. </summary>
            RendererAPI virtual ~BasicRenderer();



            /** UTILITIES **/
            /// <summary> Executes the main event loop for the rendering engine. </summary>
            RendererAPI virtual void Execute();



        protected:

            /** DATA **/
            Color4              ClearColor;
            Transform           Projection;
            GPU*                Renderer;
            ShaderPipeline*     RenderPipeline;
            Scene3D*            RenderScene;
            FrameBuffer*        RenderTarget;
            Window3D*           RenderWindow;
            string              Title;
            Camera              View;



            /** CONSTRUCTOR **/
            /// <summary> Constructs a basic renderer that can be used to display geometric primitives. </summary>
            /// <param name="title"> The title string to be displayed on the rendering window's upper border. </param>
            RendererAPI BasicRenderer(const Area& displayArea, const string& title);
            

            
            /** INITIALIZATION UTILITIES **/
            /// <summary> Initializes the framebuffer object that serves as the rendering target. </summary>
            /// <remarks>
            ///     This method gets called at program startup and whenever window resizing events are triggered via the 
            ///     <see cref="CreateSizedResources"/> method. 
            /// </remarks>            
            RendererAPI virtual void CreateRenderTarget();
            /// <summary> Initializes any resources related to rendering 3D scenes of geometric primitives. </summary>
            /// <remarks>
            ///     This base implementation performs no actions and should be overridden by any subclass that wishes 
            ///     to add new geometry to the stored scene.
            /// </remarks>
            RendererAPI virtual void CreateSceneResources();
            /// <summary> Initializes the rendering pipeline containing the shader programs used to render 3D geometry. </summary>
            RendererAPI virtual void CreateShaderPipeline();
            /// <summary> Initializes any resources that depend on the size of the size of the rendering window. </summary>
            /// <remarks>
            ///     This base implementation calls the methods <see cref="CreateRenderTarget"/> and <see cref="CreateTransformations"/> 
            ///     to initialize resources that depend explicitly on the size of the rendering window. This method is 
            ///     also called in response to window resizing events to ensure that these resources are proportioned 
            ///     correctly.
            /// </remarks>
            RendererAPI virtual void CreateSizedResources();
            /// <summary> Initializes the projection and view transformation matrices that are used to create 3D environments on 2D computer monitors. </summary
            /// <remarks>
            ///     This method gets called at program startup and whenever window resizing events are triggered via the 
            ///     <see cref="CreateSizedResources"/> method.
            /// </remarks>
            RendererAPI virtual void CreateTransformations();
            /// <summary> Initializes all rendering resources. </summary>
            /// <remarks>
            ///     This method summarily calls all other initialization methods. In order, this includes: rendering window, 
            ///     shader pipeline, sized resource, and scene resource initialization.
            /// </remarks>
            RendererAPI virtual void Initialize();



            /** PROTECTED UTILITIES **/
            /// <summary> Sets a flag that prevents the rendering engine's main event loop from executing. </summary>
            RendererAPI virtual void BreakEventLoop() { _canContinue = false; }
            /// <summary> Updates any geometry or scene-related resources while rendering. </summary>
            /// <remarks> This method gets called once near the beginning of each event loop iteration. </remarks>
            RendererAPI virtual void UpdateScene();



            
        private:
            bool    _canContinue;


    };

}