/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once
#include "Buffers/VertexBuffer.h"
#include "Geometry/Model3D.h"
#include "Spatial/Camera.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    /** FORWARD DECLARATIONS **/
    using namespace OpenGL;
    using namespace Platform;
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



    class Program
    {
        public:

            /** CONSTRUCTOR & DESTRUCTOR **/
            Program(int nargs, char** args);
            ~Program();



            /** UTILITIES **/
            /// <summary> Runs the main event loop for the program. </summary>
            void Execute();

        private:

            bool            _canContinue;
            bool            _debug;
            int             _display;
            bool            _showHelp;

            Transform       Projection;
            GPU*            Renderer;
            ShaderPipeline* RenderPipeline;
            Scene3D*        RenderScene;
            FrameBuffer*    RenderTarget;
            Window3D*       RenderWindow;
            Camera          View;
            Model3D          Cube;
            Model3D          PlaneXZ;
            Model3D          Icosahedron;
            



            /** UTILITIES **/
			void CreateRenderingPipeline();
			void CreateRenderingTarget();
			void CreateRenderingWindow();
			void CreateSceneResources();
            void CreateSizedResources();
			void CreateTransformations();
            void ParseInputArguments(int nargs, char** args);

            void BreakEventLoop();

    };
}