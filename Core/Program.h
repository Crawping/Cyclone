/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once
#include "BasicRenderer.h"
#include "Geometry/Entity3D.h"
#include "Models/Model3D.h"



namespace Cyclone
{

    /** FORWARD DECLARATIONS **/
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

    using namespace OpenGL;
    using namespace Platform;
    using namespace Renderers;
    using namespace Utilities;


    class Program: public BasicRenderer
    {
        public:

            /** CONSTRUCTOR & DESTRUCTOR **/
            Program(int nargs, char** args);
            ~Program();



            /** UTILITIES **/
            /// <summary> Runs the main event loop for the program. </summary>
            void Execute();

        protected:

			void CreateSceneResources() override;
            void CreateShaderPipeline() override;

            void UpdateScene()          override;
            

        private:

            bool            _debug;
            bool            _showHelp;

            Resource<Entity3D>         Cube;
            Resource<Entity3D>         Icosahedron;
            Resource<Entity3D>         PlaneXZ;

    };
}