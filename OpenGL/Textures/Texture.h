/* CHANGELOG
 * Written by Josh Grooms on 20160609
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"

#include "GL/OpenGLAPI.h"
#include "Interfaces/IBindable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture : public IBindable
        {
            public:

                /** PROPERTIES **/
                virtual TextureFormats Format() const { return _format; }
                virtual ulong Handle()          const { return _handle; }
                virtual uint Height()           const = 0;
                /// <summary> Gets the unique numeric identifier for the texture object on the GPU. </summary>
                virtual uint ID()               const override { return _id; }
                /// <summary> Gets whether the texture has any zero-length dimensions. </summary>
                virtual bool IsEmpty()          const = 0;
                virtual TextureTargets Target() const { return _target; }
                virtual uint Width()            const = 0;



                /** DESTRUCTOR **/
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

            protected:

                /** CONSTRUCTOR **/
                OpenGLAPI Texture(TextureFormats format, TextureTargets target);



                /** GPU RESOURCE UTILITIES **/
                /// <summary> Reserves storage space for the texture on the GPU. </summary>
                OpenGLAPI virtual void Allocate();

                OpenGLAPI virtual void Create();
                OpenGLAPI virtual void Destroy();
                virtual void Reallocate()       { Destroy(); Create(); Allocate(); }

            private:

                /** PROPERTY DATA **/
                TextureFormats  _format;
                ulong           _handle;
                uint            _id;
                TextureTargets  _target;

        };
    }
}