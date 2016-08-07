/* CHANGELOG
 * Written by Josh Grooms on 20160806
 */

#pragma once
#include "TypeDefinitions.h"
#include "Buffers/GraphicsArray.h"
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


        class CommandBuffer : public GraphicsArray<DrawCommand>
        {
            public:
                CommandBuffer();


                void BindEntity(int slot = 0) const override;
                
        };



    }
}