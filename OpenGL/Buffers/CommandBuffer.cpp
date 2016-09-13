#include "Buffers/CommandBuffer.h"
#include "GL/OpenGL.h"



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename U>
        CommandBuffer<U>::CommandBuffer() :
            ArrayBuffer<U>(BufferTypes::DrawIndirect)
        {

        }



        /** EXPLICIT TEMPLATE INSTANTIATIONS **/
        template class CommandBuffer<DrawCommand>;
        template class CommandBuffer<IndexedDrawCommand>;
    }
}
