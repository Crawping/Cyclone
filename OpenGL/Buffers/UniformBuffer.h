/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "Buffers/GraphicsArray.h"


namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class UniformBuffer : public GraphicsArray<T>
        {

            public:

                /** CONSTRUCTOR & DESTRUCTOR **/
                UniformBuffer() : GraphicsArray<T>(BufferTypes::Uniform) { }
                ~UniformBuffer() { }

        };
    }
}
