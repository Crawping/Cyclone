/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once
#include "Buffers/VertexBuffer.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    /** FORWARD DECLARATIONS **/
    namespace OpenGL
    {
        class FrameBuffer;
        class Mesh3D;
        class Quad3D;
        class Scene3D;
        class ShaderPipeline;
    }
    namespace Platform
    {
        class GPU;
        class Window3D;
    }

    using namespace OpenGL;
    using namespace Platform;



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
            Transform       View;
            Mesh3D*         TestShape;

            Quad3D*         PlaneXZ;



            /** UTILITIES **/
            void CreateSizedResources();
            void ParseInputArguments(int nargs, char** args);

            void BreakEventLoop();

    };
}