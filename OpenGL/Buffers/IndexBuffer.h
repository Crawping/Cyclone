/* CHANGELOG
 * Written by Josh Grooms on 20160901
 */

#pragma once
#include "Buffers/ArrayBuffer.h"
#include "Math/Array.h"



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
                IndexBuffer() : 
                    IndexBuffer(0, nullptr)
                {

                }
                /// <summary> Constructs a GPU buffer object that is initialized by an array of vertex indices. </summary>
                /// <param name="indices"> A reference to an array of vertex indices. </param>
                IndexBuffer(const Array<uint>& indices) :
                    IndexBuffer(indices.Count(), indices.ToArray())
                {

                }
                /// <summary> Constructs a GPU buffer object that is initialized by an array of vertex indices. </summary>
                /// <param name="n"> The number of indices present in the inputted index array. </param>
                /// <param name="indices"> A pointer to the beginning of an n-length index array. </param>
                IndexBuffer(uint n, const uint* indices) : 
                    ArrayBuffer<uint>(BufferTypes::ElementArray)
                {
                    for (uint a = 0; a < n; a++)
                        Set(a, indices[a]);
                }


                void BindEntity(int slot = 0) const override
                {
                    glBindBuffer(Type(), ID());
                }

        };
    }
}