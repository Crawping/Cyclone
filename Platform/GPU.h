/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;
        class ShaderPipeline;
    }
    
    using namespace OpenGL;



    class GPU
    {
        public:

            /** PROPERTIES **/
            //const RenderContext Context() const { return _context; }


            /** CONSTRUCTOR **/
            PlatformAPI GPU();
            PlatformAPI ~GPU();



            /** RENDERING UTILITIES **/
            void Clear();
            void Present();



        private:
                       
            struct              _gpu;
            _gpu*               Internals;

            ShaderPipeline*     _renderPipeline;
            FrameBuffer*        _renderTarget;
                


            /** PRIVATE UTILITIES **/
            void CreateRenderContext();

            void RestoreRenderingDefaults();
    };
}
