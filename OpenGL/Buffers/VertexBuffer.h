/* CHANGELOG
 * Written by Josh Grooms on 20150911
 */

#pragma once
#include "Buffers/VertexArray.h"
#include "Collections/Array.h"
#include "Collections/ArrayList.h"
#include "Collections/Array.h"
#include "Geometry/Vertex.h"



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
                uint Capacity()     const { return _data.Capacity(); }
                /// <summary> Gets the number of vertices present in the buffer. </summary>
                uint Count()        const override { return _data.Count(); }
                /// <summary> Gets the number of bytes occupied by one individual vertex element of this buffer. </summary>
                ulong Stride()      const override { return sizeof(T); }



                /** CONSTRUCTORS **/
                /// <summary> Constructs an empty GPU buffer object that can be populated with geometric vertices. </summary>
                VertexBuffer():     VertexArray(T::Layout()) { }



                /** BUFFER UTILITIES **/
                virtual void Append(const T& value)
                {
                    _data.Append(value);
                    Invalidate(Count() - 1);
                }
                virtual void Append(const ICollection<T>& values)
                {
                    uint idx = Count();
                    _data.Append(values);
                    Invalidate(idx, Count());
                }
                void Clear() override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    Invalidate(0);
                }
                virtual void Insert(uint index, const T& value)
                {
                    _data.Insert(index, value);
                    Invalidate(index, Count());
                }
                virtual void Insert(uint index, const ICollection<T>& values)
                {
                    _data.Insert(index, values);
                    Invalidate(index, Count());
                }
                virtual void Remove(uint index, uint count = 1)
                {
                    if (index >= Count()) { return; }
                    _data.Remove(index, count);
                    Invalidate(index, Count());
                }
                virtual void Set(uint index, const T& data)
                {
                    _data.Set(index, data);
                    Invalidate(index);
                }
                virtual void Set(uint index, const ICollection<T>& values)
                {
                    for (uint a = 0; a < values.Count(); a++)
                        _data.Set(index + a, values(a));
                    Invalidate(index, index + values.Count());
                }
                virtual void Update() override
                {
                    VertexArray::Update();
                    if (!NeedsUpdate()) { return; }

                    const auto& range = UpdateRange();
                    T* handles = (T*)Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    for (uint a = range(0); a < range(1); a++)
                        handles[a] = _data(a);

                    Unmap();
                    ClearUpdates();
                }

            protected:

                void Allocate(BufferAccessIntents intent, uint count) override
                {
                    VertexArray::Allocate(intent, Math::Max(count, Capacity()));
                }

            private:

                ArrayList<T>    _data;

        };
    }
}