/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "Console.h"
#include "EnumerationsGL.h"
#include "IBindable.h"
#include "TypeDefinitions.h"
#include <vector>



template<typename T>
class GraphicsBuffer : public IBindable
{
    public:

        /** PROPERTIES **/
        /// <summary> Gets the total number of bytes occupied by all data current found in this buffer. </summary>
		virtual ulong ByteSize()        const { return Count() * Stride(); }
		/// <summary> Gets the number of individual elements stored within this buffer. </summary>
		virtual uint Count()            const { return Data.size(); }
		/// <summary> Gets the unique numeric identifier for this buffer object on the GPU. </summary>
		virtual uint ID()               const { return _id; }
		/// <summary> Determines whether this buffer contains any data. </summary>
		virtual bool IsEmpty()          const { return Count() == 0; }
		/// <summary> Gets the number of bytes occupied by one individual element of this buffer. </summary>
		virtual ulong Stride()          const { return sizeof(T); }
		/// <summary> Gets an enumerator identifying how this buffer behaves on the GPU. </summary>
		virtual BufferTypes Type()      const { return _type; }



        /** DESTRUCTOR **/
		~GraphicsBuffer()
        {
            if (_id)
                glDeleteBuffers(1, &_id);
        }



        /** UTILITIES **/
		/// <summary> Removes all of the data currently stored within this buffer. </summary>
		virtual void Clear()
        {
            if (IsEmpty()) { return; }
            Data.clear();
            _reallocateFlag = true;
            _updateFlag = true;
        }
		/// <summary> Writes the contents of a single data element to the application-side memory held by this buffer. </summary>
		/// <param name="index">
		///		An integer index indicating where the element in <paramref name="data"/> will be inserted into the buffer.
		///		<para> </para>
		///		If an element already exists at this position, then its value will be overwritten by <paramref name="data"/>. <para/>
		///		If, however, this argument refers to a position at or beyond the end of the buffer storage,					  <para/>
		///		then a new storage element will be created at the requested position and a complete reallocation			  <para/>
		///		of the buffer will be scheduled for the next update pass. In any case, a content update is always 			  <para/>
		///		scheduled when invoking this function.
		/// </param>
		/// <param name="data">
		///		A reference to the data element that will be copied into the buffer on both the application and
		///		GPU sides.
		/// </param>
		/// <remarks>
		///		This method is used to either insert or modify data within this buffer, but only on the application (i.e. system
		///		memory) side. Transferring these modifications over to the corresponding GPU memory for use within shader
		///		programs requires a subsequent call to the 'Update' method of this class.
		/// </remarks>
		virtual void Set(uint index, const T& data)
        {
            if (index == Count())
            {
                Data.push_back(data);
                _reallocateFlag = true;
            }
            else
                Data[index] = data;

            _updateFlag = true;
        }
		/// <summary> Transfers all application-side data found within this buffer over to its corresponding GPU storage. </summary>
		virtual void Update()
        {
            if (!_updateFlag)       { return; }
            if (_reallocateFlag)    { Reallocate(); }

            T* handles = (T*)glMapNamedBufferRange(ID(), 0, Count() * Stride(), BufferAccessIntents::Write | BufferAccessIntents::Invalidate);
            if (!handles)
            {
                Console::WriteLine("Failed to map and update the graphics buffer GPU-side storage.");
                return;
            }
            for (uint a = 0; a < Count(); a++)
                handles[a] = Data[a];

            glUnmapNamedBuffer(ID());
            _updateFlag = false;
        }



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
		void BindEntity(int slot = 0)   const override { glBindBufferBase(Type(), slot, ID()); }
		/// <summary> Attaches any resources associated with this buffer to the rendering pipeline. </summary>
		void BindResources()            const override { }
		/// <summary> Summarily detaches this buffer and any associated resources from the rendering pipeline. </summary>
		void Unbind()                   const override { UnbindEntity(); UnbindResources(); }
		/// <summary> Detaches this buffer from the rendering pipeline. */
		void UnbindEntity()             const override { glBindBuffer(Type(), 0); }
		/// <summary> Detaches any resources associated with this buffer from the rendering pipeline. </summary>
		void UnbindResources()          const override { }



        /** OPERATORS **/
		virtual const T& operator [](int index)        { return Data[index]; }



    protected:

        /** PROTECTED PROPERTIES **/
		bool ReallocateFlag()                   const { return _reallocateFlag; }
		bool UpdateFlag()                       const { return _updateFlag; }



        /** CONSTRUCTOR **/
		GraphicsBuffer(BufferTypes type) :
            _id(0),
            _type(type),
            _reallocateFlag(false),
            _updateFlag(false)
        {
            Create();
        }
		GraphicsBuffer(BufferTypes type, uint length) :
            _id(0),
            _type(type),
            _reallocateFlag(false),
            _updateFlag(false),
            Data(length)
        {
            Create();
            Allocate();
        }


		
        /** PROTECTED UTILITIES **/
		/// <summary> Reserves memory on the GPU for storing all of the data found within this buffer. </summary>
		virtual void Allocate()
        {
            if (!IsEmpty())
                glNamedBufferStorage(ID(), Count() * Stride(), &Data[0], BufferAccessIntents::Write);
            _reallocateFlag = false;
        }
		/// <summary> Generates a new buffer object on the GPU that can be used to store data. </summary>
		virtual void Create()
        {
            if (_id)
            {
                Console::WriteLine("A GPU buffer object already exists and must be deleted before attempting to create a new one.");
                return;
            }
            glCreateBuffers(1, &_id);
        }
		/// <summary> Deletes the buffer object on the GPU. </summary>
		virtual void Destroy()
        {
            if (_id)
            {
                glDeleteBuffers(1, &_id);
                _id = 0;
            }
        }
		/// <summary> Summarily destroys, recreates, and reallocates this buffer on the GPU. </summary>
		virtual void Reallocate()
        {
            Destroy();
            Create();
            Allocate();
        }



		/** OPERATORS **/
		//virtual T& operator [](uint index)			  { return Data[index]; }

		
    private:

        /** PROPERTY DATA **/
        uint        _id;
        bool        _reallocateFlag;
        BufferTypes _type;
        bool        _updateFlag;


		/** PRIVATE DATA **/
		/// <summary> A copy of the data in the GPU buffer that is held in system memory. </summary>
		std::vector<T> Data;

};
