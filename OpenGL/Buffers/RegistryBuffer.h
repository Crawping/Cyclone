/* CHANGELOG
 * Written by Josh Grooms on 20161130
 */

#pragma once
#include "Buffers/GraphicsBuffer.h"
#include "Collections/Registry.h"



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T>
        class RegistryBuffer : public GraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of data elements stored with the buffer. </summary>
                virtual uint Count()        const override { return _data.Count(); }
                virtual ulong Stride()      const override { return sizeof(T); }
                virtual List<T> Values()    const { return _data.Values(); }



                /** UTILITIES **/
                /// <summary> Determines whether the buffer contains a data element that corresponds with a specific key. </summary>
                /// <param name="key"> The specific registry key to be tested. </param>
                /// <returns> A Boolean <c>true</c> if the key exists within the buffer, or <c>false</c> otherwise. </returns>
                virtual bool Contains(const RegistryKey<T>& key) const { return _data.Contains(key); }
                /// <summary> Removes all of the data currently stored within the buffer. </summary>
                virtual void Clear()        override
                {
                    if (IsEmpty()) { return; }
                    _data.Clear();
                    NeedsUpdate(true);
                }
                virtual void Set(const RegistryKey<T>& key, const T& value)
                {
                    _data[key] = value;
                    NeedsUpdate(true);
                }
                virtual RegistryKey<T> Register(const T& value)
                {
                    uint count = Count();
                    RegistryKey<T> key = _data.Register(value);
                    NeedsUpdate(Count() != count);
                    return key;
                }
                virtual void Remove(const RegistryKey<T>& key)
                {
                    if (!Contains(key)) { return; }
                    _data.Remove(key);
                    NeedsUpdate(true);
                }
                virtual void Update() override
                {
                    if (!NeedsUpdate()) { return; }
                    GraphicsBuffer::Update();

                    uint idx = 0;
                    T* handles = (T*)Map(BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
                    for (const T& v : Values())
                        handles[idx++] = v;

                    Unmap();
                }

            protected:

                /** CONSTRUCTOR **/
                RegistryBuffer(BufferTypes type) : GraphicsBuffer(type) { }

            private:

                /** DATA **/
                Registry<T> _data;
        };
    }
}
