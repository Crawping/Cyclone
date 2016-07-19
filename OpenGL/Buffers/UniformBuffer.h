/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "Buffers/GraphicsBuffer.h"


namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class UniformBuffer : public GraphicsBuffer<T>
        {

            public:

                /** CONSTRUCTOR & DESTRUCTOR **/
                UniformBuffer() : GraphicsBuffer<T>(BufferTypes::Uniform) { }
                ~UniformBuffer() { }

        };
    }
}
