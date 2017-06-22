/* CHANGELOG
 * Written by Josh Grooms on 20150911
 */

#pragma once
#include "TypeDefinitions.h"
#include "Buffers/VertexArray.h"
#include "Collections/Vector.h"
#include "Geometry/Vertex.h"
#include "GL/OpenGLAPI.h"
#include <vector>



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that represents a GPU buffer containing a list of vertices that make up geometric primitives. </summary>
        /// <typeparam name="T"> The type name of the vertex data structure used by the buffer. </typeparam>
        template<typename T = Vertex>
        class VertexBuffer: public VertexArray
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of vertices present in the buffer. </summary>
                uint Count()    const override { return Data.size(); }
                /// <summary> Gets the number of bytes occupied by one individual vertex element of this buffer. </summary>
                ulong Stride()  const override { return sizeof(T); }



                /** CONSTRUCTORS **/
                /// <summary> Constructs an empty GPU buffer object that can be populated with geometric vertices. </summary>
                VertexBuffer() : 
                    VertexBuffer(0, nullptr)
                {

                }
                /// <summary> Constructs a GPU buffer object that is initialized by an array of vertex data. </summary>
                /// <param name="vertices"> A reference to an array of vertex data. </param>
                VertexBuffer(const Vector<T>& vertices) :
                    VertexBuffer(vertices.Count(), vertices.ToArray())
                {
                    
                }
                /// <summary> Constructs a GPU buffer object that is initialized by an array of vertex data. </summary>
                /// <param name="n"> The number of vertices present in the inputted vertex array. </param>
                /// <param name="vertices"> A pointer to the beginning of an n-length vertex array. </param>
                VertexBuffer(uint n, const T* vertices) :
                    VertexArray(T::Layout())
                {
                    for (uint a = 0; a < n; a++)
                        Set(a, vertices[a]);
                }



                /** BUFFER UTILITIES **/
                virtual void Append(const T& data)
                {
                    Data.push_back(data);
                    NeedsUpdate(true);
                }
                virtual void Clear() override
                {
                    if (IsEmpty()) { return; }
                    Data.clear();
                    GraphicsBuffer::Clear();
                }
                virtual void Remove(uint index)
                {
                    if (index >= Count()) { return; }
                    Data.erase(Data.begin() + index);
                    NeedsUpdate(true);
                }
                virtual void Set(uint index, const T& data)
                {
                    if (index == Count())
                        return Append(data);
                    else
                        Data[index] = data;

                    NeedsUpdate(true);
                }
                virtual void Update() override
                {
                    if (!NeedsUpdate()) { return; }

                    GraphicsBuffer::Update();
                    T* handles = (T*)GraphicsBuffer::Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    if (handles)
                        for (uint a = 0; a < Count(); a++)
                            handles[a] = Data[a];

                    GraphicsBuffer::Unmap();
                }

            private:

                std::vector<T> Data;

        };
    }
}