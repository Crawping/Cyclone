#include "Buffers/CommandBuffer.h"
#include "GL/OpenGL.h"


namespace Cyclone
{
    namespace OpenGL
    {

        CommandBuffer::CommandBuffer() : 
            ArrayBuffer<DrawCommand>(BufferTypes::DrawIndirect)
        {

        }
        void CommandBuffer::BindEntity(int slot) const
        {
            glBindBuffer(Type(), ID());
        }

        IndexedCommandBuffer::IndexedCommandBuffer() :
            ArrayBuffer<IndexedDrawCommand>(BufferTypes::DrawIndirect)
        {

        }
        void IndexedCommandBuffer::BindEntity(int slot) const
        {
            glBindBuffer(Type(), ID());
        }
    }
}