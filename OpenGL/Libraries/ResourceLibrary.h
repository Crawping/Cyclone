/* CHANGELOG
 * Written by Josh Grooms on 20161125
 */

#pragma once
#include "Buffers/RegistryBuffer.h"
#include "IO/Event.h"



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class ResourceLibrary : public RegistryBuffer<T>
        {
            public:

                /** CONSTRUCTOR **/
                ResourceLibrary() :
                    RegistryBuffer<T>(BufferTypes::Uniform)
                {

                }
        };
    }
}
