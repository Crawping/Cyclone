/* CHANGELOG
 * Written by Josh Grooms on 20150911
 */

#pragma once
#include "TypeDefinitions.h"
#include "Buffers/GraphicsArray.h"
#include "GL/OpenGLAPI.h"
#include "Math/Array.h"
#include "Spatial/Vertex.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class VertexBuffer : public GraphicsArray<Vertex>
        {

            public:

                /** CONSTRUCTORS & DESTRUCTOR **/

                OpenGLAPI VertexBuffer();
                /// <summary> Constructs a buffer that is initialized by an array of vertex data. </summary>
                /// <param name="vertices"> A reference to an array of vertex data. </param>
		        OpenGLAPI VertexBuffer(const Array<Vertex>& vertices);
                /// <summary> Constructs a buffer that is initialized by an array of vertex data. </summary>
                /// <param name="n"> The number of vertices present in the inputted vertex array. </param>
                /// <param name="vertices"> A pointer to the beginning of an n-length vertex array. </param>
		        OpenGLAPI VertexBuffer(uint n, const Vertex* vertices);
		        OpenGLAPI ~VertexBuffer();



                /** UTILITIES **/
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


                OpenGLAPI void Create()                 override;
                OpenGLAPI void Destroy()                override;


            private:
		        
		        /// <summary> The numeric identifier for the vertex array object (VAO) on the GPU. </summary>
                uint            VAOID;

        };
    }
}