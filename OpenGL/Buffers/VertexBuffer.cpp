#include "VertexBuffer.h"



/** CONSTRUCTORS & DESTRUCTOR **/
VertexBuffer::VertexBuffer(const Array<Vertex>& vertices) : 
	GraphicsBuffer<Vertex>(BufferTypes::Uniform, vertices.Count()),
	VAOID(0)
{
	for (int a = 0; a < Count(); a++)
		Set(a, vertices(a));
}
VertexBuffer::VertexBuffer(uint n, const Vertex* vertices) :
    GraphicsBuffer<Vertex>(BufferTypes::Uniform, n),
    VAOID(0)
{
	for (uint a = 0; a < n; a++)
		Set(a, vertices[a]);

    glCreateVertexArrays(1, &VAOID);
    
    BindEntity();
        //glNamedBufferStorage(ID(), Count() * Stride(), &Data[0], 0);

        glVertexArrayAttribBinding(VAOID, 0, 0);
        glVertexArrayAttribFormat(VAOID, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Position));
        glEnableVertexArrayAttrib(VAOID, 0);

        glVertexArrayAttribBinding(VAOID, 1, 0);
        glVertexArrayAttribFormat(VAOID, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, UV));
        glEnableVertexArrayAttrib(VAOID, 1);

        glVertexArrayVertexBuffer(VAOID, 0, ID(), 0, Stride());
    UnbindEntity();
}
VertexBuffer::~VertexBuffer()
{
    if (VAOID)
        glDeleteVertexArrays(1, &VAOID);
}



/** BINDING UTILITIES **/
void VertexBuffer::Bind(int slot) const
{
    if (IsEmpty()) { return; }
    BindEntity(slot);
    BindResources();
}
void VertexBuffer::BindEntity(int slot) const
{
    glBindVertexArray(VAOID);
}
void VertexBuffer::BindResources() const
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
void VertexBuffer::Unbind() const
{
    UnbindResources();
    UnbindEntity();
}
void VertexBuffer::UnbindEntity() const
{
    glBindVertexArray(0);
}
void VertexBuffer::UnbindResources() const
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
