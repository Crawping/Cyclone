/* CHANGELOG
 * Written by Josh Grooms on 20150911
 */

#pragma once
#include "TypeDefinitions.h"
#include "Buffers/VertexArray.h"
#include "GL/OpenGLAPI.h"
#include "Math/Array.h"
#include "Geometry/Vertex.h"
#include <vector>



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T = Vertex::Standard>
        class VertexBuffer : public VertexArray
        {

            public:

                /** PROPERTIES **/
                uint Count() const override { return Data.size(); }
                ulong Stride() const override { return sizeof(T); }


                /** CONSTRUCTORS & DESTRUCTOR **/

                VertexBuffer() : 
                    VertexBuffer(0, nullptr)
                {

                }
                /// <summary> Constructs a buffer that is initialized by an array of vertex data. </summary>
                /// <param name="vertices"> A reference to an array of vertex data. </param>
                VertexBuffer(const Array<T>& vertices) :
                    VertexBuffer(vertices.Count(), vertices.ToArray())
                {
                    
                }
                /// <summary> Constructs a buffer that is initialized by an array of vertex data. </summary>
                /// <param name="n"> The number of vertices present in the inputted vertex array. </param>
                /// <param name="vertices"> A pointer to the beginning of an n-length vertex array. </param>
                VertexBuffer(uint n, const T* vertices) :
                    VertexArray(T().Layout())
                {
                    Create();
                    for (uint a = 0; a < n; a++)
                        Set(a, vertices[a]);
                    Update();
                }
                ~VertexBuffer()
                {

                }



                /** BUFFER UTILITIES **/
                virtual void Add(const T& data)
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
                        return Add(data);
                    else
                        Data[index] = data;

                    NeedsUpdate(true);
                }
                virtual void Update() override
                {
                    if (!NeedsUpdate()) { return; }

                    GraphicsBuffer::Update();
                    T* handles = (T*)GraphicsBuffer::Map();
                    for (uint a = 0; a < Count(); a++)
                        handles[a] = Data[a];

                    GraphicsBuffer::Unmap();
                }



            private:
                std::vector<T> Data;

        };
    }
}