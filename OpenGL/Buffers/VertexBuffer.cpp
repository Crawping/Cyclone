#include "Buffers/VertexBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        VertexBuffer::VertexBuffer() :
            VertexBuffer(0, nullptr)
        {

        }
        VertexBuffer::VertexBuffer(const Array<Vertex>& vertices) : 
            VertexBuffer(vertices.Count(), vertices.ToArray())	        
        {
	        
        }
        VertexBuffer::VertexBuffer(uint n, const Vertex* vertices) :
            ArrayBuffer<Vertex>(BufferTypes::Array, n),
            VAOID(0)
        {
	        for (uint a = 0; a < n; a++)
		        Set(a, vertices[a]);
            Update();
        }
        VertexBuffer::~VertexBuffer()
        {
            if (VAOID)
                glDeleteVertexArrays(1, &VAOID);
        }



        /** BINDING UTILITIES **/
        void VertexBuffer::BindEntity(int slot) const
        {            
            glBindVertexArray(VAOID);
        }
        void VertexBuffer::BindResources()      const
        {
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        }
        void VertexBuffer::UnbindEntity()       const
        {
            glBindVertexArray(0);
        }
        void VertexBuffer::UnbindResources()    const
        {
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }



        /** PROTECTED UTILITIES **/
        void VertexBuffer::Create()
        {
            ArrayBuffer<Vertex>::Create();
            glCreateVertexArrays(1, &VAOID);

            glVertexArrayAttribBinding(VAOID, 0, 0);
            glVertexArrayAttribFormat(VAOID, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Position));
            glEnableVertexArrayAttrib(VAOID, 0);

            glVertexArrayAttribBinding(VAOID, 1, 0);
            glVertexArrayAttribFormat(VAOID, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, UV));
            glEnableVertexArrayAttrib(VAOID, 1);

            glVertexArrayVertexBuffer(VAOID, 0, ID(), 0, Stride());
        }
        void VertexBuffer::Destroy()
        {
            if (VAOID)
            {
                glDeleteVertexArrays(1, &VAOID);
                VAOID = 0;
            }
            ArrayBuffer<Vertex>::Destroy();
        }
    }
}