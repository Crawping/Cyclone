/* CHANGELOG
 * Written by Josh Grooms on 20160725
 */

#pragma once
#include "Collections/BST.h"
#include "Buffers/GraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that holds and maintains a binary search tree (BST) associated with a data buffer on the GPU. </summary>
        /// <typeparam name="T"> The type of the key used to index into the tree. </typeparam>
        /// <typeparam name="U"> The type of the values stored in the tree. </typeparam>
        template<typename T, typename U>
        class MapBuffer: public GraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of individual elements stored within this buffer. </summary>
                virtual uint Count()            const override { return _data.Count(); }
                /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
                virtual ulong Stride()          const override { return sizeof(U); }
                /// <summary> Gets a list of keys that can be used to index into the buffer. </summary>
                virtual List<T> Keys()          const { return _data.Keys(); }
                /// <summary> Gets a list of data elements that are stored within the buffer. </summary>
                virtual List<U> Values()        const { return _data.Values(); }



                /** UTILITIES **/
                /// <summary> Determines whether the buffer stores a value corresponding with a specific key. </summary>
                /// <returns> A Boolean <c>true</c> if the buffer contains the given key, or <c>false</c> otherwise. </returns>
                /// <param name="key"> The key to be tested. </param>
                virtual bool Contains(const T& key)             const { return _data.Contains(key); }
                /// <summary> Removes all of the data currently stored within this buffer. </summary>
                virtual void Clear()                            override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    Invalidate(0);
                }
                /// <summary> Retrieves the linear array index at which a particular key is stored. </summary>
                /// <returns> An integer that represents the current linear array position of the given key in the buffer. </returns>
                /// <param name="key"> The key whose linear index is to be found. </param>
                virtual uint IndexOf(const T& key)              const { return _data.IndexOf(key); }
                /// <summary> Inserts or overwrites a specific value in the buffer. </summary>
                /// <param name="key"> The key to be associated with the data element. </param>
                /// <param name="value"> The data element to be stored within the buffer. </param>
                virtual void Set(const T& key, const U& value)
                {
                    _data.Insert(key, value);
                    Invalidate(_data.IndexOf(key), Count());
                }
                /// <summary> Erases the data element corresponding with a specific key from the buffer. </summary>
                /// <param name="key"> The key associated with the value to be removed. </param>
                virtual void Remove(const T& key)
                {
                    if (!Contains(key)) { return; }
                    uint idx = _data.IndexOf(key);
                    _data.Remove(key);
                    Invalidate(idx, Count());
                }
                /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
                virtual void Update()                           override
                {
                    GraphicsBuffer::Update();
                    if (!NeedsUpdate()) { return; }

                    const auto& range = UpdateRange();
                    U* handles = (U*)Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    for (uint a = range(0); a < range(1); a++)
                        handles[a] = _data(a);

                    Unmap();
                    ClearUpdates();
                }

            protected:

                /** CONSTRUCTOR **/
                MapBuffer(BufferTypes type) : GraphicsBuffer(type) { }

            private:

                /** DATA **/
                BST<T, U>       _data;
        };
    }
}