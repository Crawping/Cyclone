/* CHANGELOG
 * Written by Josh Grooms on 20160726
 */

#pragma once
#include "EnumerationsGL.h"
#include "Collections/ArrayList.h"
#include "Buffers/GraphicsBuffer.h"
//#include <vector>



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
		        /// <summary> Gets the number of individual elements stored within this buffer. </summary>
		        virtual uint Count()            const override { return Data.Count(); }
		        /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
		        virtual ulong Stride()          const override { return sizeof(T); }



                /** UTILITIES **/
		        /// <summary> Removes all of the data currently stored within this buffer. </summary>
		        virtual void Clear()                        override
                {
                    if (IsEmpty()) { return; }
                    Data.Clear();
                    GraphicsBuffer::Clear();
                }
                /// <summary> Inserts a value at the end of the buffer. </summary>
                /// <param name="data"> The data element to be copied and inserted into the buffer. </param>
                virtual void Append(const T& data)
                {
                    Data.Append(data);
                    NeedsUpdate(true);
                }
                /// <summary> Inserts multiple values at the end of the buffer. </summary>
                /// <param name="data"> A generic collection of data elements to be copied and inserted into the buffer. </param>
                virtual void Append(const ICollection<T>& data)
                {
                    Data.Append(data);
                    NeedsUpdate(true);
                }
                /// <summary> Removes the data element at a specific array index from the GPU buffer. </summary>
                /// <param name="index"> The array index of the data element to be removed from the buffer. </param>
                virtual void Remove(uint index)
                {
                    if (index >= Count()) { return; }
                    Data.Remove(index);
                    NeedsUpdate(true);
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
                    else
                        Data(index) = data;

                    NeedsUpdate(true);
                }

                virtual void Set(uint index, const ICollection<T>& data)
                {
                    for (uint a = 0; a < data.Count(); a++)
                        Data(index + a) = data(a);
                    NeedsUpdate(true);
                }
		        /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
		        virtual void Update()                       override
                {
                    if (!NeedsUpdate())     { return; }

                    GraphicsBuffer::Update();

                    T* handles = (T*)GraphicsBuffer::Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    if (handles)
                        for (uint a = 0; a < Count(); a++)
                            handles[a] = Data(a);

                    GraphicsBuffer::Unmap();
                }



                /** OPERATORS **/
		        virtual const T& operator ()(int index)        const { return Data(index); }

            protected:

                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty one-dimensional storage buffer whose data can be accessed on the GPU. </summary>
                /// <param name="type"> One of the <see cref="BufferTypes"/> enumerators specifying the type of buffer to be created. </param>
		        ArrayBuffer(BufferTypes type): GraphicsBuffer(type) { }
                /// <summary> Constructs a one-dimensional storage buffer of a specified size whose data can accessed on the GPU. </summary>
                /// <param name="type"> One of the <see cref="BufferTypes"/> enumerators specifying the type of buffer to be created. </param>
                /// <param name="length"> The desired number of data elements to stored within the buffer. </param>
		        ArrayBuffer(BufferTypes type, uint length) :
                    GraphicsBuffer(type),
                    Data(length)
                {
                    Allocate();
                }

            private:

		        /** PRIVATE DATA **/
		        /// <summary> A copy of the data in the GPU buffer that is held in system memory. </summary>
		        ArrayList<T> Data;

        };
    }
}
