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
        /// <summary> A class that holds and manages properties controlling how texture data is read within shader programs. </summary>
        class TextureSampler : public virtual IBindable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the color of the border that surrounds a texture. </summary>
                Color4 BorderColor()            const { return _borderColor; }
                /// <summary> Gets the wrapping behavior applied when attempting to sample a texture at out-of-bounds coordinates. </summary>
                WrapModes EdgeWrap()            const { return _edgeWrap; }
                /// <summary> Gets the unique numeric identifier for the sampler object on the GPU. </summary>
                uint ID()                       const override { return _id; }
                /// <summary> Gets the base level of detail at which a texture will be sampled. </summary>
                int LOD()                       const { return _lod; }
                /// <summary> Gets the filtering behavior applied when a texture is enlarged. </summary>
                TextureFilters MagnifyFilter()  const { return _magnifyFilter; }
                /// <summary> Gets the maximum level of detail at which a texture can be sampled. </summary>
                int MaxLOD()                    const { return _maxLOD; }
                /// <summary> Gets the filtering behavior applied when they a texture is shrunk. </summary>
                TextureFilters MinifyFilter()   const { return _minifyFilter; }
                /// <summary> Gets the minimum level of detail at which a texture can be sampled. </summary>
                int MinLOD()                    const { return _minLOD; }

                /// <summary> Sets the color of the border that surrounds a texture. </summary>
                OpenGLAPI TextureSampler& BorderColor(const Color4& value);
                /// <summary> Sets the wrapping behavior applied when attempting to sample a texture at out-of-bounds coordinates. </summary>
                OpenGLAPI TextureSampler& EdgeWrap(WrapModes value);
                /// <summary> Sets the level of detail at which a texture can be sampled. </summary>
                OpenGLAPI TextureSampler& LOD(int value);
                /// <summary> Sets the filtering behavior applied when a texture is enlarged. </summary>
                OpenGLAPI TextureSampler& MagnifyFilter(TextureFilters value);
                /// <summary> Sets the maximum level of detail at which a texture can be sampled. </summary>
                OpenGLAPI TextureSampler& MaxLOD(int value);
                /// <summary> Sets the filtering behavior applied when a texture is shrunk. </summary>
                OpenGLAPI TextureSampler& MinifyFilter(TextureFilters value);
                /// <summary> Sets the minimum level of detail at which a texture can be sampled. </summary>
                OpenGLAPI TextureSampler& MinLOD(int value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new default texture sampler object. </summary>
                OpenGLAPI TextureSampler();
                OpenGLAPI TextureSampler(TextureSampler&& other);
                OpenGLAPI TextureSampler(const TextureSampler& other);
                /// <summary> Destroys a texture sampler object and frees its GPU resources. </summary>
                OpenGLAPI ~TextureSampler();



                /** UTILITIES **/
                OpenGLAPI void Bind(int slot = 0)           const override;
                OpenGLAPI void BindEntity(int slot = 0)     const override;
                OpenGLAPI void BindResources()              const override;

                OpenGLAPI void Unbind()                     const override;
                OpenGLAPI void UnbindEntity()               const override;
                OpenGLAPI void UnbindResources()            const override;

                OpenGLAPI void Update()                     const;



                /** OPERATORS **/
                OpenGLAPI TextureSampler& operator =(TextureSampler&& other);
                OpenGLAPI TextureSampler& operator =(const TextureSampler& other);

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
