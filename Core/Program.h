/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once


namespace Cyclone
{
    namespace OpenGL
    {
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

            bool    _debug;
            int     _display;
            bool    _showHelp;

            GPU*        Renderer;
            Window3D*   RenderingWindow;

            ShaderPipeline* RenderPipeline;
        


            /** UTILITIES **/
            void ParseInputArguments(int nargs, char** args);
    };
}