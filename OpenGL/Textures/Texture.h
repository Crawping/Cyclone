/* CHANGELOG
 * Written by Josh Grooms on 20160609
 */

#pragma once
#include "EnumerationsGL.h"
#include "IBindable.h"
#include "OpenGLAPI.h"
#include "TypeDefinitions.h"


namespace Cyclone
{
    namespace OpenGL
    {
        class OpenGLAPI Texture : public IBindable
        {
            public:

                /** PROPERTIES **/
                virtual TextureFormats Format() const { return _format; }
                virtual ulong Handle()          const { return _handle; }
                /* ID - Gets the unique numeric identifier for this texture object on the GPU. */
                virtual uint ID()               const override { return _id; }
                /* ISEMPTY - Gets whether this texture has any zero-length dimensions. */
                virtual bool IsEmpty()          const = 0;
                virtual TextureTargets Target() const { return _target; }



                /** DESTRUCTOR **/
                virtual ~Texture();



                /** BINDING UTILITIES **/
                void Bind(int slot = 0)         const override { BindEntity(slot); BindResources(); }
                void BindEntity(int slot = 0)   const override;
                void BindResources()            const override { }
                void Unbind()                   const override { UnbindResources(); UnbindEntity(); }
                void UnbindEntity()             const override;
                void UnbindResources()          const override { }



                /** TEXTURE UTILITIES **/
                virtual void GenerateMipmap();
                virtual void MakeNonresident();
                virtual void MakeResident();

            protected:

                /** CONSTRUCTOR **/
                Texture(TextureFormats format, TextureTargets target);



                /** GPU RESOURCE UTILITIES **/
                virtual void Allocate()         = 0;
                virtual void Create();
                virtual void Destroy();
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