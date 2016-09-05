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

        struct DrawCommand
        {
            uint VertexCount;
            uint InstanceCount;
            uint FirstVertex;
            uint FirstInstance;

            constexpr DrawCommand(uint nVertices, uint nInstances, uint firstIndex, uint firstVertex, uint firstInstance) :
                VertexCount(nVertices),
                InstanceCount(nInstances),
                FirstVertex(firstVertex),
                FirstInstance(firstInstance)
            {

            }
        };

        struct IndexedDrawCommand
        {
            uint VertexCount;
            uint InstanceCount;
            uint FirstIndex;
            uint FirstVertex;
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

                /** CONSTRUCTOR **/
                OpenGLAPI CommandBuffer();



                /** BINDING UTILITIES **/
                OpenGLAPI void BindEntity(int slot = 0) const override;
                
        };

    }
}