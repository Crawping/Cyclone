/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once



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


            GPU();
            ~GPU();


        private:
                
            struct              _gpu;
            _gpu*               Internals;

            ShaderPipeline*     _renderPipeline;
            FrameBuffer*        _renderTarget;
                


            /** PRIVATE UTILITIES **/
            void CreateRenderContext();
            
    };
}
