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
        class Texture : public IBindable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the depth of the texture in pixels. </summary>
                virtual uint Depth()            const { return (uint)_size.Z; }
                virtual TextureFormats Format() const { return _format; }
                virtual ulong Handle()          const { return _handle; }
                /// <summary> Gets the height of the texture in pixels. </summary>
                virtual uint Height()           const { return (uint)_size.Y; }
                /// <summary> Gets the unique numeric identifier for the texture object on the GPU. </summary>
                virtual uint ID()               const override { return _id; }
                /// <summary> Gets whether the texture has any zero-length dimensions. </summary>
                virtual bool IsEmpty()          const { return Height() && Width() && Depth(); }

                virtual bool MipmapCount()      const { return _mipmapCount; }

                virtual bool NeedsUpdate()      const { return _needsUpdate; }
                /// <summary> Gets the (width, height, depth) of the texture in pixels. </summary>
                virtual const Vector3& Size()   const { return _size; }

                virtual TextureTargets Target() const { return _target; }
                /// <summary> Gets the width of the texture in pixels. </summary>
                virtual uint Width()            const { return (uint)_size.X; }

                OpenGLAPI virtual Texture& Format(TextureFormats value);
                OpenGLAPI virtual Texture& MipmapCount(uint value);
                OpenGLAPI virtual Texture& Size(const Vector3& value);
                OpenGLAPI virtual Texture& Target(TextureTargets value);



                /** CONSTRUCTOR & DESTRUCTOR **/                
                OpenGLAPI Texture(const Vector3& size, TextureFormats format, TextureTargets target);
                OpenGLAPI virtual ~Texture();



                /** BINDING UTILITIES **/
                void Bind(int slot = 0)                 const override { BindEntity(slot); BindResources(); }
                OpenGLAPI void BindEntity(int slot = 0) const override;
                void BindResources()                    const override { }

                void Unbind()                           const override { UnbindResources(); UnbindEntity(); }
                OpenGLAPI void UnbindEntity()           const override;
                void UnbindResources()                  const override { }



                /** TEXTURE UTILITIES **/
                OpenGLAPI virtual void GenerateMipmap();
                OpenGLAPI virtual void MakeNonresident();
                OpenGLAPI virtual void MakeResident();
                OpenGLAPI virtual void Update();

            protected:

                /** CONSTRUCTOR **/
                OpenGLAPI Texture();



                /** GPU RESOURCE UTILITIES **/
                /// <summary> Reserves storage space for the texture on the GPU. </summary>
                /// <remarks>
                ///     This method allocates the storage space needed to hold the texture on the GPU. It requires 
                ///     an existing texture object (created with the <see cref="Create"/> method of this class) and 
                ///     sizing information 
                /// </remarks>
                OpenGLAPI virtual void Allocate();
                /// <summary> Creates the texture object on the GPU. </summary>
                /// <remarks>
                ///     
                /// </remarks>
                OpenGLAPI virtual void Create();
                OpenGLAPI virtual void Destroy();
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