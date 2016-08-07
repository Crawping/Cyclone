#include "Buffers/CommandBuffer.h"
#include "GL/OpenGL.h"


namespace Cyclone
{
    namespace OpenGL
    {

        CommandBuffer::CommandBuffer() : 
            GraphicsArray<DrawCommand>(BufferTypes::DrawIndirect)
        {

        }
        void CommandBuffer::BindEntity(int slot) const
        {
            glBindBuffer(Type(), ID());
        }
    }
}