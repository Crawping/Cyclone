/* CHANGELOG
 * Written by Josh Grooms on 20150911
 */

#pragma once
#include "Array.h"
#include "GraphicsBuffer.h"
#include "OpenGLAPI.h"
#include "TypeDefinitions.h"
#include "Vertex.h"



class VertexBuffer : public GraphicsBuffer<Vertex>
{

    public:

        /** CONSTRUCTORS & DESTRUCTOR **/
		OpenGLAPI VertexBuffer(const Array<Vertex>& vertices);
        /// <summary> Constructs a buffer that is initialized by an array of vertex data. </summary>
		OpenGLAPI VertexBuffer(uint n, const Vertex* vertices);
		OpenGLAPI ~VertexBuffer();



        /** UTILITIES **/
		/// <summary> Attaches this buffer and its resources to the active vertex shader on the GPU. </summary>
		/// <remarks>
		/// This method is an efficient shortcut that calls both 'BindEntity' and 'BindResources' in order to fully attach a 
		///	vertex buffer to the GPU shader program. This is usually what should be called when dealing with vertex buffers.
		/// </remarks>
		OpenGLAPI void Bind(int slot = 0)         const override;
		/// <summary> Attaches this buffer to the active vertex shader on the GPU. </summary>
		/// <remarks>
		///	This method binds the vertex array object (VAO) to the GPU, but does not enable any of the vertex attributes
		/// ('BindResources' takes care of this).Typically, this will be called through the 'Bind' method.However, it is provided
		/// here because there are times when only the VAO should be enabled without also enabling its attributes.
		/// </remarks>
		OpenGLAPI void BindEntity(int slot = 0)   const override;
        /// <summary> Attaches resources within this buffer to their corresponding variables in the vertex shader. </summary>
		OpenGLAPI void BindResources()            const override;
		/// <summary> Detaches this buffer and its resources from the GPU rendering pipeline. </summary>
		OpenGLAPI void Unbind()                   const override;

		OpenGLAPI void UnbindEntity()             const override;

		OpenGLAPI void UnbindResources()          const override;



    private:
		/// <summary> The numeric identifier for the vertex array object (VAO) on the GPU. </summary>
        uint            VAOID;

};
