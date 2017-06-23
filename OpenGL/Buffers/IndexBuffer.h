/* CHANGELOG
 * Written by Josh Grooms on 20160901
 */

#pragma once
#include "Buffers/ArrayBuffer.h"
#include "Collections/Vector.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that represents a GPU buffer containing a list of indices that dictate vertex rendering order. </summary>
        class IndexBuffer : public ArrayBuffer<uint>
        {

            public:

                /** CONSTRUCTORS **/
                /// <summary> Constructs an empty GPU buffer object that can be populated with a list of vertex indices. </summary>
                IndexBuffer(): 
                    ArrayBuffer<uint>(BufferTypes::ElementArray)
                {

                }

        };
    }
}