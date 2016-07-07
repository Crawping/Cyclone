/* CHANGELOG
 * Written by Josh Grooms on 20151016
 */

#pragma once
#include "EnumerationsGL.h"
#include "Color4.h"
#include "OpenGLAPI.h"



/* TEXTURESAMPLER - A data structure that holds and manages texture sampling parameters. */
struct OpenGLAPI TextureSampler
{
    /* BORDERCOLOR - The color of the border that surrounds the texture. */
    Color4              BorderColor;
    /* EDGEWRAP - Controls the wrapping behavior when attempting to sample textures at out-of-bounds coordinates. */
    WrapModes           EdgeWrap;
    /* LOD - The base level of detail at which a texture will be sampled. */
    int                 LOD;
    /* MAGNIFYFILTER - Controls how textures are filtered when they are enlarged to fit within their rendering space. */
    TextureFilters      MagnifyFilter;
    /* MAXLOG - The maximum level of detail at which textures can be sampled. */
    int                 MaxLOD;
    /* MINIFYFILTER - Controls how textures are filtered when they are shrunk to fit within their rendering space. */
    TextureFilters      MinifyFilter;
    /* MINLOD - The minimum level of detail at which textures can be sampled. */
    int                 MinLOD;


    /* TEXTURESAMPLER - Constructs a default, fully initialized sampler parameter data structure. */
    TextureSampler();


    /** UTILITIES **/
    /* BIND - Sets the texture sampling parameters for a texture on the GPU. */
    void Bind() const;
    /* FILTERS - Sets both the magnification and minification filters of a texture to the same value. */
    TextureSampler& Filters(TextureFilters filter) { MagnifyFilter = MinifyFilter = filter; return *this; }
    /* REPORT - Generates a human-readable string detailing the current internal state of this data structure. */
    string Report() const;
};
