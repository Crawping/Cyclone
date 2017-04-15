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
        class OpenGLAPI IGraphicsBuffer : 
            public virtual IBindable, 
            public virtual IUpdatable
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

        /// <summary> A data structure that holds a graphics buffer and the slot to which it will be bound. </summary>
        struct BufferBinding
        {
            /// <summary> A valid graphics buffer that is to be bound to the GPU for rendering. </summary>
            const IGraphicsBuffer&  Buffer;
            /// <summary> The resource slot number to which the graphics buffer will be bound. </summary>
            uint                    Slot;
        };
    }
}
