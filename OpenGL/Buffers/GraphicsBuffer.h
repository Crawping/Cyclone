/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "Console.h"
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"
#include "Interfaces/IBindable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class GraphicsBuffer : public IBindable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the total number of bytes occupied by all data current found in this buffer. </summary>
		        virtual ulong ByteSize()        const { return Count() * Stride(); }
		        /// <summary> Gets the number of individual elements stored within this buffer. </summary>
                virtual uint Count()            const = 0;
		        /// <summary> Gets the unique numeric identifier for this buffer object on the GPU. </summary>
		        virtual uint ID()               const { return _id; }
		        /// <summary> Determines whether this buffer contains any data. </summary>
		        virtual bool IsEmpty()          const { return Count() == 0; }
		        /// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
                virtual ulong Stride()          const = 0;
		        /// <summary> Gets an enumerator identifying how this buffer behaves on the GPU. </summary>
		        virtual BufferTypes Type()      const { return _type; }



                /** DESTRUCTOR **/
                virtual ~GraphicsBuffer();



                /** UTILITIES **/
		        /// <summary> Removes all of the data currently stored within this buffer. </summary>
                virtual void Clear();
		        /// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
                virtual void Update();




                /** IBINDABLE OVERRIDES **/
		        /// <summary> Summarily attaches this buffer and any associated resources to the rendering pipeline. </summary>
		        /// <remarks> Currently, binding is aborted if this buffer object is empty. </remarks>
		        void Bind(int slot = 0)         const override
                {
                    if (IsEmpty()) { return; }
                    BindResources();
                    BindEntity(slot);
                }
		        /// <summary> Attaches this buffer to the rendering pipeline at the designated resource slot. </summary>
                void BindEntity(int slot = 0)   const override;
		        /// <summary> Attaches any resources associated with this buffer to the rendering pipeline. </summary>
		        void BindResources()            const override { }
		        /// <summary> Summarily detaches this buffer and any associated resources from the rendering pipeline. </summary>
		        void Unbind()                   const override { UnbindEntity(); UnbindResources(); }
		        /// <summary> Detaches this buffer from the rendering pipeline. */
                void UnbindEntity()             const override;
		        /// <summary> Detaches any resources associated with this buffer from the rendering pipeline. </summary>
		        void UnbindResources()          const override { }



            protected:

                /** PROTECTED PROPERTIES **/
                /// <summary> Gets whether this buffer needs to be reallocated on the GPU. </summary>
                bool NeedsReallocation()                const { return _gpuCount != Count(); }
                /// <summary> Gets whether this buffer needs any kind of update on the GPU side. </summary>
                bool NeedsUpdate()                      const { return _updateFlag || NeedsReallocation(); }
		        bool ReallocateFlag()                   const { return _reallocateFlag; }
		        bool UpdateFlag()                       const { return _updateFlag; }
                /// <summary> Sets whether this buffer needs any kind of update on the GPU side. </summary>
                /// <remarks>
                /// 
                /// </remarks>
                void NeedsUpdate(bool value)
                {
                    if (NeedsUpdate()) { return; }
                    _updateFlag = value;
                }


                /** CONSTRUCTOR **/
		        GraphicsBuffer(BufferTypes type) :
                    _id(0),
                    _type(type),
                    _reallocateFlag(false),
                    _updateFlag(false)
                {
                    Create();
                }


		
                /** PROTECTED UTILITIES **/
		        /// <summary> Reserves memory on the GPU for storing all of the data found within this buffer. </summary>
                virtual void Allocate();
		        /// <summary> Generates a new buffer object on the GPU that can be used to store data. </summary>
                virtual void Create();
		        /// <summary> Deletes the buffer object on the GPU. </summary>
                virtual void Destroy();
                /// <summary> Generates an array of handles representing this buffer's resources on the GPU. </summary>
                /// <returns> A pointer-to-void that can be freely cast to the type of data held by this buffer. </returns>
                /// <remarks>
                ///     Always call <see cref="Unmap"/> immediately after finishing work with GPU resources.
                /// </remarks>
                virtual void* Map();
		        /// <summary> Summarily destroys, recreates, and reallocates this buffer on the GPU. </summary>
		        virtual void Reallocate()
                {
                    Destroy();
                    Create();
                    Allocate();
                }
                /// <summary> Destroys the array of handles that were created by <see cref="Map"/>. </summary>
                /// <remarks>
                ///     This method should always be called after editing GPU resources using <see cref="Map"/>.
                /// </remarks>
                virtual void Unmap();

		
            private:

                /** PROPERTY DATA **/
                uint        _gpuCount;
                uint        _id;
                bool        _reallocateFlag;
                BufferTypes _type;
                bool        _updateFlag;
                
        };
    }
}