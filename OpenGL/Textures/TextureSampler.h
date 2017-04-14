/* CHANGELOG
 * Written by Josh Grooms on 20151016
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IBindable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A data structure that holds and manages texture sampling parameters. </summary>
        class TextureSampler : public virtual IBindable
        {
            public:
                /// <summary> The color of the border that surrounds the texture. </summary>
                Color4 BorderColor()            const { return _borderColor; }
                /// <summary> Controls the wrapping behavior when attempting to sample textures at out-of-bounds coordinates. </summary>
                WrapModes EdgeWrap()            const { return _edgeWrap; }

                uint ID()                       const override { return _id; }
                /// <summary> The base level of detail at which a texture will be sampled. </summary>
                int LOD()                       const { return _lod; }
                /// <summary> Controls how textures are filtered when they are enlarged to fit within their rendering space. </summary>
                TextureFilters MagnifyFilter()  const { return _magnifyFilter; }
                /// <summary> The maximum level of detail at which textures can be sampled. </summary>
                int MaxLOD()                    const { return _maxLOD; }
                /// <summary> Controls how textures are filtered when they are shrunk to fit within their rendering space. </summary>
                TextureFilters MinifyFilter()   const { return _minifyFilter; }
                /// <summary> The minimum level of detail at which textures can be sampled. </summary>
                int MinLOD()                    const { return _minLOD; }

                OpenGLAPI TextureSampler& BorderColor(const Color4& value);
                OpenGLAPI TextureSampler& EdgeWrap(WrapModes value);
                OpenGLAPI TextureSampler& LOD(int value);
                OpenGLAPI TextureSampler& MagnifyFilter(TextureFilters value);
                OpenGLAPI TextureSampler& MaxLOD(int value);
                OpenGLAPI TextureSampler& MinifyFilter(TextureFilters value);
                OpenGLAPI TextureSampler& MinLOD(int value);



                OpenGLAPI TextureSampler();
                OpenGLAPI ~TextureSampler();

                OpenGLAPI void Bind(int slot = 0)           const override;
                OpenGLAPI void BindEntity(int slot = 0)     const override;
                OpenGLAPI void BindResources()              const override;

                OpenGLAPI void Unbind()                     const override;
                OpenGLAPI void UnbindEntity()               const override;
                OpenGLAPI void UnbindResources()            const override;

                OpenGLAPI void Update()                     const;

            private:

                Color4          _borderColor;
                WrapModes       _edgeWrap;
                uint            _id;
                int             _lod;
                TextureFilters  _magnifyFilter;
                int             _maxLOD;
                TextureFilters  _minifyFilter;
                int             _minLOD;
                mutable bool    _needsUpdate;



                
        };
    }
}
