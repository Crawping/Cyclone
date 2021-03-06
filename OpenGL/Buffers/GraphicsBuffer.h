/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"
#include "Collections/Array.h"
#include "Interfaces/IGraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class GraphicsBuffer : public IGraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of bytes occupied by all data current found in this buffer. </summary>
		        virtual ulong ByteSize()        const { return Count() * Stride(); }
		        /// <summary> Gets the unique numeric identifier for this buffer object on the GPU. </summary>
		        virtual uint ID()               const override { return _id; }
		        /// <summary> Determines whether this buffer contains any data. </summary>
		        virtual bool IsEmpty()          const override { return Count() == 0; }
                /// <summary> Gets whether this buffer has data updates queued for transfer to the GPU. </summary>
                virtual bool NeedsUpdate()      const override { return _updateRange(1) > _updateRange(0); }
		        /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
                virtual ulong Stride()          const = 0;
		        /// <summary> Gets an enumerator identifying how this buffer behaves on the GPU. </summary>
		        virtual BufferTypes Type()      const { return _type; }



                /** DESTRUCTOR **/
                OpenGLAPI virtual ~GraphicsBuffer();



                /** BUFFER UTILITIES **/
		        /// <summary> Transfers all application-side data fo und within this buffer over to its corresponding GPU storage. </summary>
                OpenGLAPI virtual void Update();


                
                /** IBINDABLE OVERRIDES **/
		        /// <summary> Summarily attaches this buffer and any associated resources to the rendering pipeline. </summary>
		        /// <remarks> Currently, binding is aborted if this buffer object is empty. </remarks>
                OpenGLAPI void Bind(int slot = 0)       const override;
		        /// <summary> Attaches this buffer to the rendering pipeline at the designated resource slot. </summary>
                OpenGLAPI void BindEntity(int slot = 0) const override;
		        /// <summary> Attaches any resources associated with this buffer to the rendering pipeline. </summary>
		        void BindResources()                    const override { }
		        /// <summary> Summarily detaches this buffer and any associated resources from the rendering pipeline. </summary>
                OpenGLAPI void Unbind()                 const override;
		        /// <summary> Detaches this buffer from the rendering pipeline. */
                OpenGLAPI void UnbindEntity()           const override;
		        /// <summary> Detaches any resources associated with this buffer from the rendering pipeline. </summary>
		        void UnbindResources()                  const override { }
                
            protected:

                /** PROTECTED PROPERTIES **/
                /// <summary> Gets whether this buffer needs to be reallocated on the GPU. </summary>
                bool NeedsReallocation()                const { return Count() > _gpuCount; }

                const Array<uint, 2>& UpdateRange()     const { return _updateRange; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new data buffer on the GPU for use in shader pipelines. </summary>
                /// <param name="type"> A type enumerator defining the purpose of this buffer. </param>
                OpenGLAPI GraphicsBuffer(BufferTypes type);



                /** PROTECTED UTILITIES **/
		        /// <summary> Reserves memory on the GPU for storing all of the data found within this buffer. </summary>
                OpenGLAPI virtual void Allocate(BufferAccessIntents intent, uint count);

                OpenGLAPI virtual void ClearUpdates();
		        /// <summary> Generates a new buffer object on the GPU that can be used to store data. </summary>
                OpenGLAPI virtual void Create();
		        /// <summary> Deletes the buffer object on the GPU. </summary>
                OpenGLAPI virtual void Destroy();

                OpenGLAPI virtual void Invalidate(uint index);
                OpenGLAPI virtual void Invalidate(uint idxA, uint idxB);
                /// <summary> Generates an array of handles representing this buffer's resources on the GPU. </summary>
                /// <returns> A pointer-to-void that can be freely cast to the type of data held by this buffer. </returns>
                /// <remarks>
                ///     Always call <see cref="Unmap"/> immediately after finishing work with GPU resources.
                /// </remarks>
                OpenGLAPI virtual void* Map(BufferAccessIntents intent);
		        /// <summary> Summarily destroys, recreates, and reallocates this buffer on the GPU. </summary>
                OpenGLAPI virtual void Reallocate(uint count);
                /// <summary> Destroys the array of handles that were created by <see cref="Map"/>. </summary>
                /// <remarks>
                ///     This method should always be called after editing GPU resources using <see cref="Map"/>.
                /// </remarks>
                OpenGLAPI virtual void Unmap();

            private:

                /** PROPERTY DATA **/
                uint            _gpuCount;
                uint            _id;
                //bool            _needsUpdate;
                BufferTypes     _type;
                Array<uint, 2>  _updateRange;

        };
    }
}
