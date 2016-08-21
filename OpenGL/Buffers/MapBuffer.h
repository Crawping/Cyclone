/* CHANGELOG
 * Written by Josh Grooms on 20160725
 */

#pragma once
#include "Buffers/GraphicsBuffer.h"
#include <map>



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
                virtual uint Count()            const override { return Data.size(); }
                /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
                virtual ulong Stride()          const override { return sizeof(U); }



                /** UTILITIES **/
                /// <summary> Removes all of the data currently stored within this buffer. </summary>
                virtual void Clear()                            override
                {
                    if (IsEmpty()) { return; }
                    Data.clear();
                    NeedsUpdate(true);
                }
                virtual void Set(const T& key, const U& value)
                {
                    Data[key] = value;
                    NeedsUpdate(true);
                }

                virtual void Remove(const T& key)
                {
                    if (Data.count(key))
                    {
                        Data.erase(key);
                        NeedsUpdate(true);
                    }
                }
                /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
                virtual void Update()                           override
                {
                    if (!NeedsUpdate()) { return; }
                    GraphicsBuffer::Update();

                    U* handles = (U*)GraphicsBuffer::Map();
                    if (!handles)
                    {
                        Console::WriteLine("Failed to map and update the graphics buffer GPU-side storage.");
                        return;
                    }

                    uint idx = 0;
                    for (const auto& kvp : Data)
                        handles[idx++] = kvp.second;

                    GraphicsBuffer::Unmap();
                }



            protected:

                /** CONSTRUCTOR **/
                MapBuffer(BufferTypes type) : GraphicsBuffer(type) { }



            private:

                /** DATA **/
                std::map<T, U>  Data;
        };
    }
}