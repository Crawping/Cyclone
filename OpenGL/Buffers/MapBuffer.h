/* CHANGELOG
 * Written by Josh Grooms on 20160725
 */

#pragma once
#include "Collections/BST.h"
#include "Collections/List.h"
#include "Buffers/GraphicsBuffer.h"
//#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A class that holds and maintains a map object associated with a data buffer on the GPU. </summary>
        template<typename T, typename U>
        class MapBuffer : public GraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of individual elements stored within this buffer. </summary>
                virtual uint Count()            const override { return _data.Count(); }
                /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
                virtual ulong Stride()          const override { return sizeof(U); }

                virtual List<T> Keys()          const { return _data.Keys(); }

                virtual List<U> Values()        const { return _data.Values(); }



                /** UTILITIES **/

                virtual bool Contains(const T& key)             const { return _data.Contains(key); }
                /// <summary> Removes all of the data currently stored within this buffer. </summary>
                virtual void Clear()                            override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    NeedsUpdate(true);
                }
                virtual uint IndexOf(const T& key)              const
                {
                    return _data.IndexOf(key);
                }
                virtual void Set(const T& key, const U& value)
                {
                    _data.Insert(key, value);
                    NeedsUpdate(true);
                }

                virtual void Remove(const T& key)
                {
                    if (Contains(key))
                    {
                        _data.Remove(key);
                        NeedsUpdate(true);
                    }
                }
                /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
                virtual void Update()                           override
                {
                    if (!NeedsUpdate()) { return; }
                    GraphicsBuffer::Update();

                    uint idx = 0;
                    U* handles = (U*)GraphicsBuffer::Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    for (const U& d : _data.Values())
                        handles[idx++] = d;

                    GraphicsBuffer::Unmap();
                }

                

            protected:

                const BST<T, U>& Data() const { return _data; }

                /** CONSTRUCTOR **/
                MapBuffer(BufferTypes type) : GraphicsBuffer(type) { }

                virtual const U& Get(const T& key) const { return _data[key]; }

            private:

                /** DATA **/
                BST<T, U>   _data;
        };
    }
}