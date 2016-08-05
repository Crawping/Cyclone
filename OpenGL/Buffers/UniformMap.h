/* CHANGELOG
 * Written by Josh Grooms on 20160727
 */

#pragma once
#include "Buffers/GraphicsMap.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that holds and maintains a map object associated with a uniform buffer on the GPU. </summary>
        template<typename T, typename U>
        class UniformMap : public GraphicsMap<T, U>
        {
            public:
                UniformMap() : GraphicsMap<T, U>(BufferTypes::Uniform) { }
                ~UniformMap() { }
        };
    }
}

