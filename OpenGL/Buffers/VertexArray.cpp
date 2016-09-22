#include "Buffers/VertexArray.h"
#include "Geometry/Vertex.h"
#include "GL/OpenGL.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        VertexArray::VertexArray(const Vector<VertexAttribute>& layout) :
            GraphicsBuffer(BufferTypes::Array),
            Layout(layout),
            VAOID(0)
        {

        }
        VertexArray::~VertexArray()
        {
            if (VAOID)
                glDeleteVertexArrays(1, &VAOID);
        }



        /** BINDING UTILITIES **/
        void VertexArray::BindEntity(int slot)  const
        {
            glBindVertexArray(VAOID);
        }
        void VertexArray::BindResources()       const
        {
            for (uint a = 0; a < Layout.Count(); a++)
                glEnableVertexAttribArray(a);
        }
        void VertexArray::UnbindEntity()        const
        {
            glBindVertexArray(0);
        }
        void VertexArray::UnbindResources()     const
        {
            for (uint a = 0; a < Layout.Count(); a++)
                glDisableVertexAttribArray(a);
        }



        /** PROTECTED UTILITIES **/
        void VertexArray::Create()
        {
            GraphicsBuffer::Create();
            glCreateVertexArrays(1, &VAOID);

            for (uint a = 0; a < Layout.Count(); a++)
            {
                glVertexArrayAttribBinding(VAOID, a, 0);
                glVertexArrayAttribFormat(VAOID, a, Layout(a).Count, Layout(a).Format, GL_FALSE, Layout(a).Offset);
                glEnableVertexArrayAttrib(VAOID, a);
            }

            glVertexArrayVertexBuffer(VAOID, 0, ID(), 0, Stride());
        }
        void VertexArray::Destroy()
        {
            if (VAOID)
            {
                glDeleteVertexArrays(1, &VAOID);
                VAOID = 0;
            }
            GraphicsBuffer::Destroy();
        }

    }
}