#include "Buffers/GraphicsBuffer.h"
#include "IO/Console.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** DESTRUCTOR **/
        GraphicsBuffer::GraphicsBuffer(BufferTypes type) : 
            _gpuCount(0),
            _id(0),
            _type(type),
            _needsUpdate(false)
        {

        }
        GraphicsBuffer::~GraphicsBuffer()
        {
            if (_id)
                glDeleteBuffers(1, &_id);
        }



        /** PUBLIC UTILITIES **/
        void GraphicsBuffer::Clear()
        {
            NeedsUpdate(true);
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
            if (NeedsReallocation()) { Reallocate(); }
            _needsUpdate = false;
        }



        /** PROTECTED UTILITIES **/
        void GraphicsBuffer::Allocate(BufferAccessIntents intent)
        {
            if (!IsEmpty())
                glNamedBufferStorage(ID(), ByteSize(), NULL, intent);
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
        void* GraphicsBuffer::Map(BufferAccessIntents intent)
        {
            return glMapNamedBufferRange(ID(), 0, ByteSize(), intent);
        }
        void GraphicsBuffer::Unmap()
        {
            glUnmapNamedBuffer(ID());
        }
    }
}