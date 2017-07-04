#include "Buffers/GraphicsBuffer.h"
#include "GL/OpenGL.h"
#include "IO/Console.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** DESTRUCTOR **/
        GraphicsBuffer::GraphicsBuffer(BufferTypes type) : 
            _gpuCount(0),
            _id(0),
            _type(type)
            //_needsUpdate(false)
        {

        }
        GraphicsBuffer::~GraphicsBuffer()
        {
            if (_id)
                glDeleteBuffers(1, &_id);
        }



        /** BINDING METHODS **/
        void GraphicsBuffer::Bind(int slot)             const
        {
            if (NeedsUpdate())
                Console::WriteLine("WARNING: The buffer being bound has updates queued but not yet applied.");

            if (IsEmpty()) { return; }
            BindEntity(slot);
            BindResources();
        }
        void GraphicsBuffer::BindEntity(int slot)       const
        {
            switch (Type())
            {
                case BufferTypes::DrawIndirect:
                case BufferTypes::ElementArray:
                    glBindBuffer(Type(), ID());
                    break;

                default:
                    glBindBufferBase(Type(), slot, ID());
                    break;
            }
        }
        void GraphicsBuffer::Unbind()                   const
        {
            UnbindResources(); 
            UnbindEntity();
        }
        void GraphicsBuffer::UnbindEntity()             const
        {
            glBindBuffer(Type(), 0);
        }
        void GraphicsBuffer::Update()
        {
            if (NeedsReallocation())
                Reallocate(Count());
        }



        /** PROTECTED UTILITIES **/
        void GraphicsBuffer::Allocate(BufferAccessIntents intent, uint count)
        {
            if (!IsEmpty())
                glNamedBufferStorage(ID(), count * Stride(), NULL, intent);
            _gpuCount = count;
        }
        void GraphicsBuffer::ClearUpdates()
        {
            _updateRange = { Count(), 0 };
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
        void GraphicsBuffer::Invalidate(uint index)             { Invalidate(index, index + 1); }
        void GraphicsBuffer::Invalidate(uint idxA, uint idxB)
        {
            _updateRange =
            {
                Math::Clamp( Math::Min(_updateRange(0), idxA), 0U, Count() ),
                Math::Clamp( Math::Max(_updateRange(1), idxB), 0U, Count() ),
            };
        }
        void* GraphicsBuffer::Map(BufferAccessIntents intent)
        {
            return glMapNamedBufferRange(ID(), 0, ByteSize(), intent);
        }
        void GraphicsBuffer::Reallocate(uint count)
        {
            Destroy();
            Create();
            Allocate(BufferAccessIntents::Write, count);
        }
        void GraphicsBuffer::Unmap()
        {
            glUnmapNamedBuffer(ID());
        }

    }
}