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

                virtual uint Count()        const override { return _data.Count(); }
                virtual ulong Stride()      const override { return sizeof(T); }
                virtual List<T> Values()    const { return _data.Values(); }


                virtual bool Contains(const RegistryKey<T>& key) const { return _data.Contains(key); }
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
                    if (Count() != count)
                        NeedsUpdate(true);

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
