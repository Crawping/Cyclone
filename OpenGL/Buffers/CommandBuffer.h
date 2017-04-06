/* CHANGELOG
 * Written by Josh Grooms on 20160806
 */

#pragma once
#include "TypeDefinitions.h"
#include "Buffers/ArrayBuffer.h"
#include "GL/OpenGLAPI.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A structure containing the parameters needed to indirectly render vertex data. </summary>
        struct DrawCommand
        {
            /// <summary> The total number of vertices to be rendered by the command. </summary>
            uint VertexCount;
            /// <summary> The total number of times the rendering command will be executed on the GPU. </summary>
            /// <remarks>
            ///     Any given rendering command can be executed multiple times in order to produce copies of rendered entities. 
            ///     These copies, or 'instances', can then be differentiated from one another by through the use of a separate 
            ///     buffer containing per-instance data, which is indexed via the <see cref="FirstInstance"/> member of this 
            ///     same structure.
            /// </remarks>
            uint InstanceCount;
            /// <summary> The position of the first vertex data structure within the vertex buffer. </summary>
            /// <remarks>
            ///     Vertices that make up the geometry in a rendered scene are often thrown together in a single vertex buffer 
            ///     object. This parameter gives the GPU an index into that buffer where the first vertex (of potentially many)
            ///     associated with the drawing command resides.
            /// </remarks>
            uint FirstVertex;
            /// <summary> The position of the first entity data structure within the per-entity buffer. </summary>
            uint FirstInstance;

            constexpr DrawCommand(uint nVertices, uint nInstances, uint firstIndex, uint firstVertex, uint firstInstance) :
                VertexCount(nVertices),
                InstanceCount(nInstances),
                FirstVertex(firstVertex),
                FirstInstance(firstInstance)
            {

            }
        };

        /// <summary> A structure containing the parameters needed to indirectly render indexed vertex data. </summary>
        struct IndexedDrawCommand
        {
            /// <summary> The total number of vertices to be rendered by the command. </summary>
            uint VertexCount;
            /// <summary> The total number of times the rendering command will be executed on the GPU. </summary>
            /// <remarks>
            ///     Any given rendering command can be executed multiple times in order to produce copies of rendered entities. 
            ///     These copies, or 'instances', can then be differentiated from one another by through the use of a separate 
            ///     buffer containing per-instance data, which is indexed via the <see cref="FirstInstance"/> member of this 
            ///     same structure.
            /// </remarks>
            uint InstanceCount;
            /// <summary> The position of the first vertex index within the index buffer. </summary>
            uint FirstIndex;
            /// <summary> The position of the first vertex data structure within the vertex buffer. </summary>
            /// <remarks>
            ///     Vertices that make up the geometry in a rendered scene are often thrown together in a single vertex buffer 
            ///     object. This parameter gives the GPU an index into that buffer where the first vertex (of potentially many)
            ///     associated with the drawing command resides.
            /// </remarks>
            uint FirstVertex;
            /// <summary> The position of the first entity data structure within the per-entity buffer. </summary>
            uint FirstInstance;

            constexpr IndexedDrawCommand(uint nVertices, uint nInstances, uint firstIndex, uint firstVertex, uint firstInstance) :
                VertexCount(nVertices),
                InstanceCount(nInstances),
                FirstIndex(firstIndex),
                FirstVertex(firstVertex),
                FirstInstance(firstInstance)
            {

            }
        };


        template<typename U>
        class CommandBuffer : public ArrayBuffer<U>
        {
            public:
                OpenGLAPI CommandBuffer();                
        };

    }
}