/* CHANGELOG
 * Written by Josh Grooms on 20160609
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"

#include "GL/OpenGLAPI.h"
#include "Interfaces/IBindable.h"
#include "Math/Vector4.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture3D : public IBindable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the depth of the texture in texels. </summary>
                virtual uint Depth()            const { return (uint)_size.Z; }

                virtual TextureFormats Format() const { return _format; }
                /// <summary> Gets the direct handle reference to the texture on the GPU. </summary>
                virtual ulong Handle()          const { return _handle; }
                /// <summary> Gets the height of the texture in texels. </summary>
                virtual uint Height()           const { return (uint)_size.Y; }
                /// <summary> Gets the unique numeric identifier for the texture object on the GPU. </summary>
                virtual uint ID()               const override { return _id; }
                /// <summary> Gets whether the texture has any zero-length dimensions. </summary>
                virtual bool IsEmpty()          const { return Height() && Width() && Depth(); }
                /// <summary> Gets whether the texture contains multiple samples per texel. </summary>
                virtual bool IsMultisampled()   const { return Target() == TextureTargets::Texture2DMS; }

                virtual bool IsResident()       const { return Handle() > 0; }
                /// <summary> Gets the number of mipmap levels associated with the texture. </summary>
                virtual uint MipmapCount()      const { return IsMultisampled() ? 1 : (uint)_size.W; }
                
                virtual bool NeedsUpdate()      const { return _needsUpdate; }
                /// <summary> Gets the number of samples associated with each texel of the texture. </summary>
                virtual uint SampleCount()      const { return IsMultisampled() ? (uint)_size.W : 0; }
                /// <summary> Gets the (x, y, z) size of the texture in texels. </summary>
                virtual const Vector3& Size()   const { return (Vector3)_size; }

                virtual TextureTargets Target() const { return _target; }
                /// <summary> Gets the width of the texture in texels. </summary>
                virtual uint Width()            const { return (uint)_size.X; }

                OpenGLAPI virtual Texture3D& Size(const Vector4& value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new texture object of the specified size, format, and type. </summary>
                /// <param name="size"> 
                ///     The desired (x, y, z, w) size of the texture. 
                ///     <para> </para>
                ///     Texture size is specified as a four-element vector containing width, height, depth,     <para/>
                ///     and count values, in that order. If a multisampled texture is being requested, then     <para/>
                ///     the vector's 'W' component is interpretted as the sample count. Otherwise, this value   <para/>
                ///     is interpretted as the desired number of mipmap levels for the texture's storage.
                /// </param>
                /// <param name="format"> One of the <see cref="TextureFormat"/> enumerators specifying the format of the texture's data. </param>
                /// <param name="target"> One of the <see cref="TextureTarget"/> enumerators specifying the type of the texture. </param>
                OpenGLAPI Texture3D(const Vector4& size, TextureFormats format, TextureTargets target);
                /// <summary> Destroys the texture object and all associated resources. </summary>
                OpenGLAPI virtual ~Texture3D();



                /** BINDING UTILITIES **/
                /// <summary> Summarily binds the texture object and its associated resources to the GPU rendering pipeline. </summary>
                /// <param name="slot"> The desired texture binding slot, which is <c>0</c> by default. </param>
                void Bind(int slot = 0)                 const override { BindEntity(slot); BindResources(); }
                /// <summary> Binds the texture object to the GPU rendering pipeline. </summary>
                /// <param name="slot"> The desired texture binding slot, which is <c>0</c> by default. </param>
                OpenGLAPI void BindEntity(int slot = 0) const override;
                void BindResources()                    const override { }

                void Unbind()                           const override { UnbindResources(); UnbindEntity(); }
                OpenGLAPI void UnbindEntity()           const override;
                void UnbindResources()                  const override { }



                /** TEXTURE UTILITIES **/
                /// <summary> Generates lower resolution image data to populate the mipmap levels of the texture. </summary>
                /// <remarks> 
                ///     Space for texture mipmaps must first be reserved during object allocation. If no mipmap levels 
                ///     have been allocated (i.e. the <see cref="MipmapCount"/> is zero), or the texture contains a 
                ///     zero-length dimension, or the texture target is a multisampled one, mipmap generation will 
                ///     silently fail.
                /// </remarks>
                OpenGLAPI virtual void GenerateMipmap();
                OpenGLAPI virtual void MakeNonresident();
                OpenGLAPI virtual void MakeResident();
                OpenGLAPI virtual void Update();

            protected:

                /** PROPERTIES **/
                void NeedsUpdate(bool value)    const { _needsUpdate = _needsUpdate ? true : value; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty texture object that can be manually initialized by subclasses. </summary>
                OpenGLAPI Texture3D();



                /** GPU RESOURCE UTILITIES **/
                /// <summary> Reserves storage space for the texture on the GPU. </summary>
                /// <remarks>
                ///     This method allocates the storage space needed to hold the texture on the GPU. It requires 
                ///     an existing texture object (created with the <see cref="Create"/> method of this class) and 
                ///     sizing information 
                /// </remarks>
                OpenGLAPI virtual void Allocate();
                /// <summary> Creates the texture object on the GPU. </summary>
                OpenGLAPI virtual void Create();
                /// <summary> Destroys the texture object on the GPU. </summary>
                OpenGLAPI virtual void Destroy();
                /// <summary> Summarily destroys and recreates the texture object on the GPU. </summary>
                OpenGLAPI virtual void Reallocate();

            private:

                /** PROPERTY DATA **/
                TextureFormats  _format;
                ulong           _handle;
                uint            _id;
                mutable bool    _needsUpdate;
                Vector4         _size;
                TextureTargets  _target;

        };
    }
}   