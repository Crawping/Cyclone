#include "OpenGL.h"
#include "Buffers/GraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** DESTRUCTOR **/
        GraphicsBuffer::~GraphicsBuffer()
        {
            if (_id)
                glDeleteBuffers(1, &_id);
        }



        /** PUBLIC UTILITIES **/
        void GraphicsBuffer::Clear()
        {
            _updateFlag = true;
        }



        /** BINDING METHODS **/
        void GraphicsBuffer::BindEntity(int slot = 0)   const
        {
            glBindBufferBase(Type(), slot, ID());
        }
        void GraphicsBuffer::UnbindEntity()             const
        {
            glBindBuffer(Type(), 0);
        }
        void GraphicsBuffer::Update()
        {
            if (NeedsReallocation()) { Reallocate(); }
            _updateFlag = false;
        }



        /** PROTECTED UTILITIES **/
        void GraphicsBuffer::Allocate()
        {
            if (!IsEmpty())
                glNamedBufferStorage(ID(), ByteSize(), NULL, BufferAccessIntents::Write);
            _gpuCount = Count();
        }
        void GraphicsBuffer::Create()
        {
            if (_id)
            {
                Console::WriteLine("A GPU buffer object already exists and must be deleted before attempting to create a new one.");
                return;
            }
            glCreateBuffers(1, &_id);
        }
        void GraphicsBuffer::Destroy()
        {
            if (_id)
            {
                glDeleteBuffers(1, &_id);
                _id = 0;
                _gpuCount = 0;
            }
        }
        void* GraphicsBuffer::Map()
        {
            return glMapNamedBufferRange(ID(), 0, ByteSize(), BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
        }
        void GraphicsBuffer::Unmap()
        {
            glUnmapNamedBuffer(ID());
        }
    }
}