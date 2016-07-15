/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "PlatformAPI.h"



namespace Cyclone
{
    namespace Utilities
    {
        class FrameBuffer;
        class ShaderPipeline;
    }
        
    using namespace Utilities;

    class GPU
    {
        public:

            /** PROPERTIES **/
            //const RenderContext Context() const { return _context; }


            PlatformAPI GPU();
            PlatformAPI ~GPU();


        private:
                
            struct              _gpu;
            _gpu*               Internals;

            ShaderPipeline*     _renderPipeline;
            FrameBuffer*        _renderTarget;
                


            /** PRIVATE UTILITIES **/
            void CreateRenderContext();
            
    };
}
