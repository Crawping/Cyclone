/* CHANGELOG
 * Written by Josh Grooms on 20151101
 */

#pragma once

#include "Enumerator.h"
#include "OpenGL.h"
#include "OpenGLAPI.h"



struct AccessIntents : public Enumerator
{
    enum Intents
    {
        Read                        = GL_READ_ONLY,
        ReadWrite                   = GL_READ_WRITE,
        Write                       = GL_WRITE_ONLY,
    };

	AccessIntents(enum Intents i = Read) : Enumerator((int)i) { }
};

struct BufferAccessIntents : public Flag
{
    enum Intents
    {
        Client                      = GL_CLIENT_STORAGE_BIT,
        Coherent                    = GL_MAP_COHERENT_BIT,
        Dynamic                     = GL_DYNAMIC_STORAGE_BIT,
        Invalidate                  = GL_MAP_INVALIDATE_BUFFER_BIT,
        InvalidateRange             = GL_MAP_INVALIDATE_RANGE_BIT,
        Persistent                  = GL_MAP_PERSISTENT_BIT,
        Read                        = GL_MAP_READ_BIT,
        Write                       = GL_MAP_WRITE_BIT,
    };
};

struct BufferTypes : public Enumerator
{
    enum Buffers
    {
        Array                       = GL_ARRAY_BUFFER,
        AtomicCounter               = GL_ATOMIC_COUNTER_BUFFER,
        CopyRead                    = GL_COPY_READ_BUFFER,
        CopyWrite                   = GL_COPY_WRITE_BUFFER,
        DispatchIndirect            = GL_DISPATCH_INDIRECT_BUFFER,
        DrawIndirect                = GL_DRAW_INDIRECT_BUFFER,
        ElementArray                = GL_ELEMENT_ARRAY_BUFFER,
        PixelPack                   = GL_PIXEL_PACK_BUFFER,
        PixelUnpack                 = GL_PIXEL_UNPACK_BUFFER,
        Query                       = GL_QUERY_BUFFER,
        ShaderStorage               = GL_SHADER_STORAGE_BUFFER,
        Texture                     = GL_TEXTURE_BUFFER,
        TransformFeedback           = GL_TRANSFORM_FEEDBACK_BUFFER,
        Uniform                     = GL_UNIFORM_BUFFER,
    };

    BufferTypes(enum Buffers b = Uniform) : Enumerator((int)b) { }
};

/// <summary>
/// A list of possible errors indicating issues that can arise within an OpenGL rendering pipeline.
/// </summary>
struct RenderErrors : public Enumerator
{
    enum Errors
    {
        InsufficientMemory          = GL_OUT_OF_MEMORY,
        InvalidEnum                 = GL_INVALID_ENUM,
        InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
        InvalidIndex                = GL_INVALID_INDEX,
        InvalidOperation            = GL_INVALID_OPERATION,
        InvalidValue                = GL_INVALID_VALUE,
        Nothing                     = GL_NO_ERROR,
        StackOverflow               = GL_STACK_OVERFLOW,
        StackUnderflow              = GL_STACK_UNDERFLOW,
    };

    RenderErrors(enum Errors e = Nothing) : Enumerator((int)e) { }
};

/// <summary> A list of the programmable GPU rendering stages. </summary>
struct ShaderTypes : public Enumerator
{
    enum Shaders
    {
        ComputeShader               = GL_COMPUTE_SHADER,
        GeometryShader              = GL_GEOMETRY_SHADER,
        PixelShader                 = GL_FRAGMENT_SHADER,
        VertexShader                = GL_VERTEX_SHADER,
    };

    ShaderTypes(enum Shaders s) : Enumerator((int)s) { }
};

/// <summary> A list of supported filters that can be applied to texture samplers. </summary>
struct TextureFilters : public Enumerator
{
    enum Filters
    {
        Linear                      = GL_LINEAR,
        LinearMipmapLinear          = GL_LINEAR_MIPMAP_LINEAR,
        LinearMipmapNearest         = GL_LINEAR_MIPMAP_NEAREST,
        Nearest                     = GL_NEAREST,
        NearestMipmapLinear         = GL_NEAREST_MIPMAP_LINEAR,
        NearestMipmapNearest        = GL_NEAREST_MIPMAP_NEAREST,
    };

    TextureFilters(enum Filters f = Linear) : Enumerator((int)f) { }
};

/// <summary> A list of supported formats in which textures can be stored on the GPU. </summary>
struct TextureFormats : public Enumerator
{
    enum Formats
    {
        Byte1                       = GL_R8,
        Byte2                       = GL_RG8,
        Byte3                       = GL_RGB8,
        Byte4                       = GL_RGBA8,

        DepthFloat                  = GL_DEPTH_COMPONENT32F,
        DepthInt                    = GL_DEPTH_COMPONENT32,
        DepthShort                  = GL_DEPTH_COMPONENT16,

        /// <summary> A 32-bit format containing one single-precision floating point channel. </summary>
        Float1                      = GL_R32F,
        /// <summary> A 64-bit RG format containing two single-precision floating point channels. </summary>
        Float2                      = GL_RG32F,
        /// <summary> A 96-bit RGB format containing three single-precision floating point channels. </summary>
        Float3                      = GL_RGB32F,
        /// <summary> A 128-bit RGBA format containing four single-precision floating point channels. </summary>
        Float4                      = GL_RGBA32F,

        Int1                        = GL_R32I,
        Int2                        = GL_RG32I,
        Int3                        = GL_RGB32I,
        Int4                        = GL_RGBA32I,

        Short1                      = GL_R16,
        Short2                      = GL_RG16,
        Short3                      = GL_RGB16,
        Short4                      = GL_RGBA16,

        /// <summary> A 32-bit format containing one unsigned integer channel. </summary>
        UInt1                       = GL_R32UI,
        /// <summary> A 64-bit RG format containing two unsigned integer channels. </summary>
        UInt2                       = GL_RG32UI,
        /// <summary> A 96-bit RGB format containing three unsigned integer channels. </summary>
        UInt3                       = GL_RGB32UI,
        /// <summary> A 128-bit RGBA format containing four unsigned integer channels. </summary>
        UInt4                       = GL_RGBA32UI,
    };

    TextureFormats(enum Formats f = Byte4) : Enumerator((int)f) { }

	/// <summary> Converts specific OpenGL internal format enumerators into their equivalent base format values. </summary>
	/// <remarks>
	/// OpenGL possesses several functions that distinguish between the simpler, base format values such as GL_RGBA and
	/// more specific ones such as GL_RGBA8(i.e. 8 - bits per channel RGBA).However, if the specific internal format is
	/// known, then the base format can also be determined.This method performs that conversion and makes it a bit
	/// easier to automate certain aspects of texture usage.
	/// </remarks>
    GLenum ToBaseFormat() const
    {
        switch ((int)*this)
        {
            case TextureFormats::Byte1:
            case TextureFormats::Float1:
            case TextureFormats::Int1:
            case TextureFormats::Short1:
            case TextureFormats::UInt1:
                return GL_RED;

            case TextureFormats::Byte2:
            case TextureFormats::Float2:
            case TextureFormats::Int2:
            case TextureFormats::Short2:
            case TextureFormats::UInt2:
                return GL_RG;

            case TextureFormats::Byte3:
            case TextureFormats::Float3:
            case TextureFormats::Int3:
            case TextureFormats::Short3:
            case TextureFormats::UInt3:
                return GL_RGB;

            case TextureFormats::Byte4:
            case TextureFormats::Float4:
            case TextureFormats::Int4:
            case TextureFormats::Short4:
            case TextureFormats::UInt4:
                return GL_RGBA;

            case TextureFormats::DepthFloat:
            case TextureFormats::DepthInt:
            case TextureFormats::DepthShort:
                return GL_DEPTH_COMPONENT;

			default:
				return 0;
        }
    }
};

/// <summary> A list of supported texture storage layouts. </summary>
struct TextureTargets : public Enumerator
{
    enum Targets
    {
        Texture1D                   = GL_TEXTURE_1D,
        Texture2D                   = GL_TEXTURE_2D,
        Texture3D                   = GL_TEXTURE_3D,
    };

    TextureTargets(enum Targets t = Texture2D) : Enumerator((int)t) { }
};

/* VERTEXTOPOLOGIES - A list of supported topologies that indicate the primitive geometry to be rendered.
 *
 *      Topologies describe how collections of vertices should be parsed and rendered on-screen. The enumerators provided here are
 *      intended for use in all 'glDraw' API functions as a replacement for clumsier 'GLenum mode' arguments.
 *
 *      Uninitalized instances of these enumerators default to the value of 'Triangles'.
 */
struct VertexTopologies : public Enumerator
{
    enum Topologies
    {
        Lines                       = GL_LINES,
        LineLoop                    = GL_LINE_LOOP,
        LineStrip                   = GL_LINE_STRIP,
        Points                      = GL_POINTS,
        Quads                       = GL_QUADS,
        /// <summary> Instructs the rendering pipeline to create triangles out of an array of vertices. </summary>
        Triangles                   = GL_TRIANGLES,
        TriangleFan                 = GL_TRIANGLE_FAN,
        /// <summary> Instructs the rendering pipeline to create a series of contiguous triangles out of an array of vertices. </summary>
        TriangleStrip               = GL_TRIANGLE_STRIP,
    };

    VertexTopologies(enum Topologies t = Triangles) : Enumerator((int)t) { }
};

/// <summary> A list of supported wrapping modes that control behavior when attempting to sample outside texture boundaries. </summary>
struct WrapModes : public Enumerator
{
    enum Modes
    {
        /// <summary> Constrains out-of-bounds sampling coordinates to the border of a texture. </summary>
        ClampToBorder               = GL_CLAMP_TO_BORDER,
        /// <summary> Constrains out-of-bounds sampling coordinates to the edge of a texture. </summary>
        ClampToEdge                 = GL_CLAMP_TO_EDGE,
        /* MIRRORCLAMPTOEDGE - */
        MirrorClampToEdge           = GL_MIRROR_CLAMP_TO_EDGE,
        /// <summary> Wraps out-of-bounds sampling coordinates back across the texture. </summary>
        MirrorRepeat                = GL_MIRRORED_REPEAT,
        /// <summary> Wraps out-of-bounds sampling coordinates to the opposite side of the texture. </summary>
        Repeat                      = GL_REPEAT,
    };

    WrapModes(enum Modes m = Repeat) : Enumerator((int)m) { }
};
