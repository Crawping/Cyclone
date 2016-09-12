/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "Buffers/ArrayBuffer.h"


namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class UniformBuffer : public ArrayBuffer<T>
        {

            public:

                /** CONSTRUCTOR & DESTRUCTOR **/
                UniformBuffer() : ArrayBuffer<T>(BufferTypes::Uniform) { }
                ~UniformBuffer() { }


            protected:
                void Reallocate() override
                {
                    Destroy();
                    Create();
                    Allocate(BufferAccessIntents::Write | BufferAccessIntents::Dynamic);
                }

        };
    }
}
