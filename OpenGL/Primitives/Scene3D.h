/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "Interfaces/IRenderable.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformBuffers.h"
#include "Primitives/Entity3D.h"



namespace Cyclone
{
    namespace OpenGL
    {


        class Scene3D
        {
            public:

                // Camera


                virtual void Add(const IRenderableEntity* entity);


                virtual void Remove(const IRenderableEntity* entity);


            private:

                UniformBuffer<PerEntity>    PerEntityBuffer;

        };
    }
}