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
        };


        class CommandBuffer : public ArrayBuffer<DrawCommand>
        {
            public:

                /** CONSTRUCTOR **/
                OpenGLAPI CommandBuffer();



                /** BINDING UTILITIES **/
                OpenGLAPI void BindEntity(int slot = 0) const override;
                
        };

    }
}