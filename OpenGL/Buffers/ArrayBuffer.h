/* CHANGELOG
 * Written by Josh Grooms on 20160726
 */

#pragma once
#include "EnumerationsGL.h"
#include "Collections/ArrayList.h"
#include "Buffers/GraphicsBuffer.h"
#include "Collections/Array.h"
#include "IO/Console.h"
#include "Utilities.h"



namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Utilities;

        template<typename T>
        class ArrayBuffer : public GraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                virtual uint Capacity()         const { return _data.Capacity(); }
		        /// <summary> Gets the number of individual elements stored within this buffer. </summary>
		        virtual uint Count()            const override { return _data.Count(); }
		        /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
		        virtual ulong Stride()          const override { return sizeof(T); }



                /** UTILITIES **/
                /// <summary> Inserts a value at the end of the buffer. </summary>
                /// <param name="data"> The data element to be copied and inserted into the buffer. </param>
                virtual void Append(const T& value)
                {
                    _data.Append(value);
                    Invalidate(Count() - 1);
                }
                /// <summary> Inserts multiple values at the end of the buffer. </summary>
                /// <param name="data"> A generic collection of data elements to be copied and inserted into the buffer. </param>
                virtual void Append(const ICollection<T>& value)
                {
                    uint idx = Count();
                    _data.Append(value);
                    Invalidate(idx, Count());
                }
		        /// <summary> Erases all of the data currently stored within this buffer. </summary>
		        virtual void Clear()                        override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    Invalidate(0);
                }
                /// <summary> Inserts a data element into the buffer at a specific location. </summary>
                /// <param name="index"> The linear array index at which the value will be inserted into the buffer. </param>
                /// <param name="value"> The value to be copied and inserted into the buffer. </param>
                virtual void Insert(uint index, const T& value)
                {
                    _data.Insert(index, value);
                    Invalidate(index, Count());
                }
                /// <summary> Inserts multiple data elements into the buffer at a specific location. </summary>
                /// <param name="index"> The linear array index at which to begin inserting values into the buffer. </param>
                /// <param name="values"> A generic collection of values to be copied and inserted into the buffer. </param>
                virtual void Insert(uint index, const ICollection<T>& values)
                {
                    if (values.IsEmpty()) { return; }
                    _data.Insert(index, values);
                    Invalidate(index, Count());
                }
                /// <summary> Removes the data element at a specific array index from the GPU buffer. </summary>
                /// <param name="index"> The array index of the data element to be removed from the buffer. </param>
                virtual void Remove(uint index, uint count = 1)
                {
                    if (index >= Count()) { return; }
                    _data.Remove(index, count);
                    Invalidate(index, Count());
                }
                /// <summary> Writes the contents of a single data element to the application-side memory held by this buffer. </summary>
		        /// <param name="index">
		        ///		An integer index indicating where the element in <paramref name="data"/> will be inserted into the buffer.
		        ///		<para>�</para>
		        ///		If an element already exists at this position, then its value will be overwritten by <paramref name="data"/>. <para/>
		        ///		If, however, this argument refers to a position at or beyond the end of the buffer storage,					  <para/>
		        ///		then a new storage element will be created at the requested position and a complete reallocation			  <para/>
		        ///		of the buffer will be scheduled for the next update pass. In any case, a content update is always 			  <para/>
		        ///		scheduled when invoking this function.
		        /// </param>
		        /// <param name="data">
		        ///		A reference to the data element that will be copied into the buffer on both the application and GPU sides.
		        /// </param>
		        /// <remarks>
		        ///		This method is used to either insert or modify data within this buffer, but only on the application (i.e. system
		        ///		memory) side. Transferring these modifications over to the corresponding GPU memory for use within shader
		        ///		programs requires a subsequent call to the 'Update' method of this class.
		        /// </remarks>
		        virtual void Set(uint index, const T& data)
                {
                    if (index >= Count())
                        return Append(data);

                    _data.Set(index, data);
                    Invalidate(index);
                }
                /// <summary> Overwrites multiple data elements stored within the buffer. </summary>
                /// <param name="index"> The linear array index at which to begin overwriting values in the buffer. </param>
                /// <param name="data"> A generic collection of data elements to be copied into the buffer. </param>
                virtual void Set(uint index, const ICollection<T>& data)
                {
                    if (data.IsEmpty()) { return; }
                    for (uint a = 0; a < data.Count(); a++)
                        _data.Set(index + a, data(a));

                    Invalidate(index, index + data.Count());
                }
		        /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
		        virtual void Update()                       override
                {
                    GraphicsBuffer::Update();
                    if (!NeedsUpdate()) { return; }

                    const auto& range = UpdateRange();
                    T* handles = (T*)Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    for (uint a = range(0); a < range(1); a++)
                        handles[a] = _data(a);

                    Unmap();
                    ClearUpdates();
                }



                /** OPERATORS **/
		        virtual const T& operator ()(int index)        const { return _data(index); }

            protected:

                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty one-dimensional storage buffer whose data can be accessed on the GPU. </summary>
                /// <param name="type"> One of the <see cref="BufferTypes"/> enumerators specifying the type of buffer to be created. </param>
		        ArrayBuffer(BufferTypes type): GraphicsBuffer(type) { }



                /** UTILITIES **/
                void Allocate(BufferAccessIntents intent, uint count) override
                {
                    GraphicsBuffer::Allocate(intent, Math::Max(count, Capacity()));
                }

            private:

		        /** PRIVATE DATA **/
		        /// <summary> A copy of the data in the GPU buffer that is held in system memory. </summary>
		        ArrayList<T>    _data;

        };
    }
}
