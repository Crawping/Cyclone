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
                    _updateRange = { Math::Min(_updateRange(0), Count() - 1), Count() };
                    _needsUpdate = true;
                }
                virtual void Append(const ICollection<T>& values)
                {
                    _data.Append(values);
                    _updateRange = { Math::Min(_updateRange(0), Count() - 1), Count() };
                    _needsUpdate = true;
                }
                void Clear() override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    _updateRange = { 0, 0 };
                    GraphicsBuffer::Clear();
                }
                virtual void Insert(uint index, const T& value)
                {
                    _data.Insert(index, value);
                    _updateRange = { Math::Min(_updateRange(0), index), Count() };
                    _needsUpdate = true;
                }
                virtual void Insert(uint index, const ICollection<T>& values)
                {
                    _data.Insert(index, values);
                    _updateRange = { Math::Min(_updateRange(0), index), Count() };
                    _needsUpdate = true;

                }
                virtual void Remove(uint index, uint count = 1)
                {
                    if (index >= Count()) { return; }
                    _data.Remove(index, count);
                    _updateRange = { Math::Min(_updateRange(0), index), Count() };
                    _needsUpdate = true;
                }
                virtual void Set(uint index, const T& data)
                {
                    _data.Set(index, data);
                    _updateRange = { Math::Min(_updateRange(0), index), Math::Max(_updateRange(1), index + 1) };
                    _needsUpdate = true;
                }
                virtual void Set(uint index, const ICollection<T>& values)
                {
                    for (uint a = 0; a < values.Count(); a++)
                        _data.Set(index + a, values(a));

                    _updateRange = { Math::Min(_updateRange(0), index), Math::Max(_updateRange(1), index + values.Count()) };
                    _needsUpdate = true;
                }
                virtual void Update() override
                {
                    if (NeedsReallocation())    { Reallocate(Capacity()); }
                    VertexArray::Update();
                    if (!_needsUpdate)          { return; }

                    T* handles = (T*)GraphicsBuffer::Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    if (handles)
                        for (uint a = _updateRange(0); a < _updateRange(1); a++)
                            handles[a] = _data(a);

                    GraphicsBuffer::Unmap();
                    _needsUpdate = false;
                    _updateRange = { Count(), 0 };
                }

            protected:

                void Reallocate(uint count) override
                {
                    VertexArray::Reallocate(count);
                    _updateRange = { 0, Count() };
                }

            private:

                ArrayList<T>    _data;
                bool            _needsUpdate;
                Array<uint, 2>  _updateRange;

        };
    }
}