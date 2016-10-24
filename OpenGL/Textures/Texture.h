/* CHANGELOG
 * Written by Josh Grooms on 20160609
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"

#include "GL/OpenGLAPI.h"
#include "Interfaces/IBindable.h"
#include "Math/Vector3.h"



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
                /// <remarks> This property is associated with the OpenGL bindless texturing extension and is not yet enabled for use. </remarks>                
                virtual ulong Handle()          const { return _handle; }
                /// <summary> Gets the height of the texture in texels. </summary>
                virtual uint Height()           const { return (uint)_size.Y; }
                /// <summary> Gets the unique numeric identifier for the texture object on the GPU. </summary>
                virtual uint ID()               const override { return _id; }
                /// <summary> Gets whether the texture has any zero-length dimensions. </summary>
                virtual bool IsEmpty()          const { return Height() && Width() && Depth(); }
                /// <summary> Gets the number of mipmap levels associated with the texture. </summary>
                virtual uint MipmapCount()      const { return _mipmapCount; }
                
                virtual bool NeedsUpdate()      const { return _needsUpdate; }
                /// <summary> Gets the (x, y, z) size of the texture in texels. </summary>
                virtual const Vector3& Size()   const { return _size; }

                virtual TextureTargets Target() const { return _target; }
                /// <summary> Gets the width of the texture in texels. </summary>
                virtual uint Width()            const { return (uint)_size.X; }

                OpenGLAPI virtual Texture3D& Format(TextureFormats value);
                OpenGLAPI virtual Texture3D& MipmapCount(uint value);
                OpenGLAPI virtual Texture3D& Size(const Vector3& value);
                OpenGLAPI virtual Texture3D& Target(TextureTargets value);



                /** CONSTRUCTOR & DESTRUCTOR **/                
                OpenGLAPI Texture3D(const Vector3& size, TextureFormats format, TextureTargets target);
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
                uint            _mipmapCount;
                bool            _needsUpdate;
                Vector3         _size;
                TextureTargets  _target;

        };
    }
}   