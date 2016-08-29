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
        VertexBuffer::VertexBuffer(const Array<Vertex::Standard>& vertices) : 
            VertexBuffer(vertices.Count(), vertices.ToArray())	        
        {
	        
        }
        VertexBuffer::VertexBuffer(uint n, const Vertex::Standard* vertices) :
            ArrayBuffer<Vertex::Standard>(BufferTypes::Array, n),
            VAOID(0),
            Layout(Vertex::Standard().Layout())
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
            for (uint a = 0; a < Layout.Count(); a++)
                glEnableVertexAttribArray(a);
        }
        void VertexBuffer::UnbindEntity()       const
        {
            glBindVertexArray(0);
        }
        void VertexBuffer::UnbindResources()    const
        {
            for (uint a = 0; a < Layout.Count(); a++)
                glDisableVertexAttribArray(a);
        }



        /** PROTECTED UTILITIES **/
        void VertexBuffer::Create()
        {
            ArrayBuffer<Vertex::Standard>::Create();
            glCreateVertexArrays(1, &VAOID);

            for (uint a = 0; a < Layout.Count(); a++)
            {
                glVertexArrayAttribBinding(VAOID, a, 0);
                glVertexArrayAttribFormat(VAOID, a, Layout(a).Count, Layout(a).Format, GL_FALSE, Layout(a).Offset);
                glEnableVertexArrayAttrib(VAOID, a);
            }

            glVertexArrayVertexBuffer(VAOID, 0, ID(), 0, Stride());
        }
        void VertexBuffer::Destroy()
        {
            if (VAOID)
            {
                glDeleteVertexArrays(1, &VAOID);
                VAOID = 0;
            }
            ArrayBuffer<Vertex::Standard>::Destroy();
        }
    }
}