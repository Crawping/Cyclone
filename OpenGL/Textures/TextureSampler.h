/* CHANGELOG
 * Written by Josh Grooms on 20151016
 */

#pragma once
#include "EnumerationsGL.h"
#include "GL/OpenGLAPI.h"
#include "Imaging/Color4.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> A data structure that holds and manages texture sampling parameters. </summary>
        struct OpenGLAPI TextureSampler
        {
            /// <summary> The color of the border that surrounds the texture. </summary>
            Color4              BorderColor;
            /// <summary> Controls the wrapping behavior when attempting to sample textures at out-of-bounds coordinates. </summary>
            WrapModes           EdgeWrap;
            /// <summary> The base level of detail at which a texture will be sampled. </summary>
            int                 LOD;
            /// <summary> Controls how textures are filtered when they are enlarged to fit within their rendering space. </summary>
            TextureFilters      MagnifyFilter;
            /// <summary> The maximum level of detail at which textures can be sampled. </summary>
            int                 MaxLOD;
            /// <summary> Controls how textures are filtered when they are shrunk to fit within their rendering space. </summary>
            TextureFilters      MinifyFilter;
            /// <summary> The minimum level of detail at which textures can be sampled. </summary>
            int                 MinLOD;



            /// <summary> Constructs a default, fully initialized sampler parameter data structure. </summary>
            TextureSampler();



            /// <summary> Sets the texture sampling parameters for a texture on the GPU. </summary>
            void Bind() const;
            /// <summary> Sets both the magnification and minification filters of a texture to the same value. </summary>
            TextureSampler& Filters(TextureFilters filter) { MagnifyFilter = MinifyFilter = filter; return *this; }
            /// <summary> Generates a human-readable string detailing the current internal state of this data structure. </summary>
            string Report() const;
        };
    }
}