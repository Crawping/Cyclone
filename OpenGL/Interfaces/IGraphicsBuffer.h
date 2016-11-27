/* CHANGELOG
 * Written by Josh Grooms on 20160823
 */

#pragma once
#include "GL/OpenGLAPI.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IUpdatable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> An interface that represents a generalized GPU buffer object. </summary>
        class OpenGLAPI IGraphicsBuffer : public IBindable, public IUpdatable
        {

            public:
                /// <summary> Gets the number of individual elements that are stored within the buffer. </summary>
                virtual uint Count()        const = 0;
                /// <summary> Gets whether the buffer object is currently empty. </summary>
                /// <remarks> By default, this method determines whether the returned <see cref="Count"/> value is zero. </remarks>
                virtual bool IsEmpty()      const { return Count() == 0; }
                /// <summary> Destroys any GPU- or heap-allocated resources held by the buffer. </summary>
                virtual ~IGraphicsBuffer()  { }
                /// <summary> Removes all of the data stored within the buffer. </summary>
                virtual void Clear()        = 0;

        };

        struct BufferBinding
        {
            const IGraphicsBuffer&  Buffer;
            uint                    Slot;
        };
    }
}
