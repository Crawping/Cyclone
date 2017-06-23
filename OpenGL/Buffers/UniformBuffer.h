/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "Buffers/ArrayBuffer.h"
#include "IO/Console.h"


namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class UniformBuffer: public ArrayBuffer<T>
        {

            public:

                /** CONSTRUCTOR & DESTRUCTOR **/
                UniformBuffer(): 
                    ArrayBuffer<T>(BufferTypes::Uniform) 
                { 
                    if (Stride() % 16 != 0)
                        Console::WriteLine("WARNING: A uniform buffer is being created with a type that is not aligned to a 16 byte boundary.");
                }

            protected:

                void Reallocate(uint count) override
                {
                    Destroy();
                    Create();
                    Allocate(BufferAccessIntents::Write | BufferAccessIntents::Dynamic, count);
                }

        };
    }
}
