/* CHANGELOG 
 * Written by Josh Grooms on 20160830
 */

#pragma once
#include "Buffers/GraphicsBuffer.h"
#include "Collections/Array.h"
#include "GL/OpenGLAPI.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** FORWARD DECLARATIONS**/
        struct VertexAttribute;



        /// <summary> A class that holds and manages a vertex array object (VAO) for inputting geometry to the GPU. </summary>
        class VertexArray: public GraphicsBuffer
        {

            public:

                /** DESTRUCTOR **/
                /// <summary> Frees the vertex array allocated on the GPU. </summary>
                OpenGLAPI virtual ~VertexArray();


                
                /** BINDING UTILITIES **/
                /// <summary> Attaches this buffer to the active vertex shader on the GPU. </summary>
                /// <remarks>
                ///	    This method binds the vertex array object (VAO) to the GPU, but does not enable any of the vertex attributes
                ///     (<see cref="BindResources"/> takes care of this). Typically, this will be called through the 'Bind' method. However, 
                ///     it is provided here because there are times when only the VAO should be enabled without also enabling its attributes.
                /// </remarks>
                OpenGLAPI void BindEntity(int slot = 0) const override;
                /// <summary> Attaches resources within this buffer to their corresponding variables in the vertex shader. </summary>
                /// <remarks>
                ///     This method enables the attributes of the vertex buffer on the GPU, which essentially tells the rendering device how 
                ///     to interpret the data inside of the buffer. Typically, this action will be performed automatically when calling the 
                ///     <see cref="Bind"/> method.
                /// </remarks>
                OpenGLAPI void BindResources()          const override;
                /// <summary> Detaches this buffer from the active vertex shader on the GPU. </summary>
                OpenGLAPI void UnbindEntity()           const override;
                /// <summary> Detaches any secondary resources associated with this buffer from the GPU. </summary>
                OpenGLAPI void UnbindResources()        const override;
                
            protected:

                /** CONSTRUCTORS **/
                /// <summary> Constructs a new vertex array object on the GPU. </summary>
                /// <param name="layout"> An array of attributes that define the structure of a vertex for the GPU. </param>
                OpenGLAPI VertexArray(const Vector<VertexAttribute>& layout);
                /// <summary> Constructs a new vertex array object on the GPU. </summary>
                /// <param name="layout"> An array of attributes that define the structure of a vertex for the GPU. </param>
                template<uint N> VertexArray(const Array<VertexAttribute, N>& layout) :
                    GraphicsBuffer(BufferTypes::Array),
                    Layout(N),
                    VAOID(0)
                {
                    for (uint a = 0; a < N; a++)
                        Layout(a) = layout(a);
                }

                
                /** UTILITIES **/
                /// <summary> Creates the vertex array object. </summary>
                /// <remarks>
                ///     This method complements the base <see cref="GraphicsBuffer"/> method of the same name and represents 
                ///     the specific procedure by which a vertex array resource gets created on the GPU. It first calls the 
                ///     superclass method to create an associated buffer object, then creates the vertex array object, and 
                ///     finishes by establishing vertex attribute bindings using the provided layout array. Unlike other 
                ///     buffer resources, no additional memory allocations are needed by vertex array objects.
                /// </remarks>
                OpenGLAPI void Create();
                /// <summary> Destroys the vertex array object. </summary>
                /// <remarks>
                ///     This method complements the base <see cref="GraphicsBuffer"/> method of the same name and represents 
                ///     the specific procedure by which a vertex array resource gets reclaimed on the GPU. It first destroys 
                ///     the array object and finishes by calling the superclass method to destroy the associated buffer object.
                /// </remarks>
                OpenGLAPI void Destroy();

            private:
                
                /// <summary> The numeric identifier for the vertex array object (VAO) on the GPU. </summary>
                uint                    VAOID;
                /// <summary> An array of vertex attributes that define the structure of a vertex for the GPU. </summary>
                Vector<VertexAttribute> Layout;

        };


    }
}