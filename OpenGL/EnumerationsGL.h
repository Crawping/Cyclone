/* CHANGELOG
 * Written by Josh Grooms on 20151101
 */

#pragma once

#include "Enumerator.h"
#include "TypeDefinitions.h"
#include "GL/OpenGL.h"
#include "GL/OpenGLAPI.h"

namespace
{
    using namespace Cyclone::Utilities;
}



/// <summary> A list of possible ways in which interaction with various entities can occur. </summary>
/// <remarks>
///     Note that the values of this enumeration are not equivalent to those found in <see cref="BufferAccessIntents"/>
///     and therefore cannot be used interchangeably with them. When interacting with GPU buffers, you must
///     specify access intents using the other enumerators.
/// </remarks>
struct AccessIntents : public Enumerator
{
    enum Intents
    {
        Read                        = GL_READ_ONLY,
        ReadWrite                   = GL_READ_WRITE,
        Write                       = GL_WRITE_ONLY,
    };

	constexpr AccessIntents(enum Intents i = Read) : Enumerator((int)i) { }
};

/// <summary> A list of possible ways in which interaction with GPU buffers can occur. </summary>
/// <remarks>
///     OpenGL requires that many interactions with existing GPU buffers be qualified with the user's
///     access intentions. For example, when mapping GPU buffers to system- or application-side memory,
///     OpenGL wants to know if you intend to only read data out of the buffer or if you will want to
///     write new data to it, because this may influence how and where in the GPU's memory the buffer
///     is ultimately stored.
///
///     The values of this enumeration are also flags that can be combined together through the usual
///     bitwise and/or operators.
/// </remarks>
struct BufferAccessIntents : public Flag<BufferAccessIntents>
{
    enum Intents
    {
        /// <summary> Indicates that buffer storage should be allocated on the application side rather than on the GPU. </summary>
        Client                      = GL_CLIENT_STORAGE_BIT,
        Coherent                    = GL_MAP_COHERENT_BIT,
        /// <summary> Indicates that the buffer will frequently undergo data updates. </summary>
        Dynamic                     = GL_DYNAMIC_STORAGE_BIT,
        Invalidate                  = GL_MAP_INVALIDATE_BUFFER_BIT,
        InvalidateRange             = GL_MAP_INVALIDATE_RANGE_BIT,
        /// <summary> Indicates that the buffer will remain mapped over a long period of time. </summary>
        Persistent                  = GL_MAP_PERSISTENT_BIT,
        /// <summary> Indicates that data reading operations will be performed on the buffer. </summary>
        Read                        = GL_MAP_READ_BIT,
        /// <summary> Indicates that data writing operations will be performed on the buffer. </summary>
        Write                       = GL_MAP_WRITE_BIT,
    };

    constexpr BufferAccessIntents(int i = Read) : Flag<BufferAccessIntents>(i) { }
};

/// <summary> A list of possible types of buffers that can be created on the GPU. </summary>
/// <remarks>
///     In the OpenGL documentation, these enumerators are referred to as buffer 'targets', which refers 
///     to the location in GPU memory where binding occurs. However, for most applications, calling them 
///     'types' proffers an easier understanding of the function that they serve.
/// </remarks>
struct BufferTypes : public Enumerator
{
    enum Buffers
    {
        /// <summary> A buffer that is meant to hold vertex attributes. </summary>
        Array                       = GL_ARRAY_BUFFER,
        AtomicCounter               = GL_ATOMIC_COUNTER_BUFFER,
        CopyRead                    = GL_COPY_READ_BUFFER,
        CopyWrite                   = GL_COPY_WRITE_BUFFER,
        /// <summary> A buffer that holds the commands and parameters used for indirect GPU computing. </summary>
        DispatchIndirect            = GL_DISPATCH_INDIRECT_BUFFER,
        /// <summary> A buffer that holds the commands and parameters used for indirect rendering. </summary>
        DrawIndirect                = GL_DRAW_INDIRECT_BUFFER,
        /// <summary> A buffer that holds an ordered list of indices that guide vertex rendering. </summary>
        ElementArray                = GL_ELEMENT_ARRAY_BUFFER,
        PixelPack                   = GL_PIXEL_PACK_BUFFER,
        PixelUnpack                 = GL_PIXEL_UNPACK_BUFFER,
        Query                       = GL_QUERY_BUFFER,
        /// <summary> A buffer containing data that is meant for reading and writing operations within shader programs. </summary>
        ShaderStorage               = GL_SHADER_STORAGE_BUFFER,
        /// <summary> A buffer that is meant to hold texture data. </summary>
        Texture                     = GL_TEXTURE_BUFFER,
        TransformFeedback           = GL_TRANSFORM_FEEDBACK_BUFFER,
        /// <summary> A buffer that holds uniform variables for use in shader programs. </summary>
        Uniform                     = GL_UNIFORM_BUFFER,
    };

    constexpr BufferTypes(enum Buffers b = Uniform) : Enumerator((int)b) { }
};

/// <summary> A list of possible face culling modes that can be applied to rendering on the GPU. </summary>
/// <remarks>
///     These modes are used to specify which faces of 3D geometry are ultimately displayed on a rendering 
///     target and can be used directly with the functions <see cref="glEnable"/> and <see cref="glDisable"/>. 
///     By default, the front face of any geometry is defined as the side on which vertex ordering proceeds 
///     in a counterclockwise fashion, while the back face has a clockwise vertex ordering.
/// </remarks>
struct CullingModes : public Enumerator
{
    enum Modes
    {
        /// <summary> Prevents the culling of the front and back faces of any geometry. </summary>
        None                        = 0,
        /// <summary> Prevents the rendering of the back face of any geometry. </summary>
        Back                        = GL_BACK,
        /// <summary> Prevents the rendering of the front face of any geometry. </summary>
        Front                       = GL_FRONT,
        /// <summary> Prevents the rendering of the front and back faces of any geometry. </summary>
        FrontAndBack                = GL_FRONT_AND_BACK,
    };

    constexpr CullingModes(enum Modes m = None) : Enumerator((int)m) { }
};

/// <summary> A list of numeric storage formats supported by OpenGL. </summary>
struct NumericFormats : public Enumerator
{
    enum Formats
    {
        /// <summary> An 8-bit signed byte format. </summary>
        Byte                        = GL_BYTE,
        /// <summary> A 64-bit double-precision floating point format. </summary>
        Double                      = GL_DOUBLE,
        Fixed                       = GL_FIXED,
        /// <summary> A 32-bit single-precision floating point format. </summary>
        Float                       = GL_FLOAT,
        /// <summary> A 32-bit signed integer format. </summary>
        Int                         = GL_INT,
        PackedInt                   = GL_INT_2_10_10_10_REV,
        PackedFloat                 = GL_UNSIGNED_INT_10F_11F_11F_REV,
        PackedUInt                  = GL_UNSIGNED_INT_2_10_10_10_REV,
        /// <summary> A 16-bit signed integer format. </summary>
        Short                       = GL_SHORT,
        /// <summary> A 16-bit half-precision floating point format. </summary>
        ShortFloat                  = GL_HALF_FLOAT,
        /// <summary> An 8-bit unsigned byte format. </summary>
        UByte                       = GL_UNSIGNED_BYTE,
        /// <summary> A 32-bit unsigned integer format. </summary>
        UInt                        = GL_UNSIGNED_INT,
        /// <summary> A 16-bit unsigned integer format. </summary>
        UShort                      = GL_UNSIGNED_SHORT,
    };

    constexpr NumericFormats(enum Formats f = UByte) : Enumerator((int)f) { }

    /// <summary> Gets the number of bits required to store a single value of a specific numeric format. </summary>
    uint BitSize() const
    {
        switch (Value)
        {
            case Byte:
            case UByte:         return 8;

            case Short:
            case ShortFloat:
            case UShort:        return 16;

            case Fixed:
            case Float:
            case Int:
            case PackedInt:
            case PackedFloat:
            case PackedUInt:
            case UInt:          return 32;

            case Double:        return 64;

            default:            return 0;
        }
    }
};

/// <summary> A list of possible errors indicating issues that can arise within an OpenGL rendering pipeline. </summary>
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

    constexpr RenderErrors(enum Errors e = Nothing) : Enumerator((int)e) { }
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

    constexpr ShaderTypes(enum Shaders s) : Enumerator((int)s) { }
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

    constexpr TextureFilters(enum Filters f = Linear) : Enumerator((int)f) { }
};

/// <summary> A list of supported formats in which color buffers and textures can be stored on the GPU. </summary>
struct TextureFormats : public Enumerator
{
    enum Formats
    {
        /// <summary> An 8-bit format for color buffers and textures containing one byte channel. </summary>
        Byte1                       = GL_R8,
        /// <summary> A 16-bit RG format for color buffers and textures containing two byte channels. </summary>
        Byte2                       = GL_RG8,
        /// <summary> A 24-bit RGB format for color buffers and textures containing three byte channels. </summary>
        Byte3                       = GL_RGB8,
        /// <summary> A 32-bit RGBA format for color buffers and textures containing four byte channels. </summary>
        Byte4                       = GL_RGBA8,

        /// <summary> A 32-bit format for depth buffers containing single-precision floating point values. </summary>
        DepthFloat                  = GL_DEPTH_COMPONENT32F,
        /// <summary> A 32-bit format for depth buffers containing integer values. </summary>
        DepthInt                    = GL_DEPTH_COMPONENT32,
        /// <summary> A 16-bit format for depth buffers containing half-precision floating point values. </summary>
        DepthShort                  = GL_DEPTH_COMPONENT16,
        /// <summary> A 32-bit format for combined depth and stencil buffers (24-bit int depth, 8-bit int stencil). </summary>
        DepthStencil                = GL_DEPTH24_STENCIL8,
        /// <summary> A 40-bit format for combined depth and stencil buffers (32-bit float depth, 8-bit int stencil). </summary>
        DepthStencilFloat           = GL_DEPTH32F_STENCIL8,

        /// <summary> A 32-bit format for color buffers and textures containing one single-precision floating point channel. </summary>
        Float1                      = GL_R32F,
        /// <summary> A 64-bit RG format containing two single-precision floating point channels. </summary>
        Float2                      = GL_RG32F,
        /// <summary> A 96-bit RGB format containing three single-precision floating point channels. </summary>
        Float3                      = GL_RGB32F,
        /// <summary> A 128-bit RGBA format containing four single-precision floating point channels. </summary>
        Float4                      = GL_RGBA32F,

        /// <summary> A 32-bit format for color buffers and textures containing one signed integer channel. </summary>
        Int1                        = GL_R32I,
        /// <summary> A 64-bit RG format for color buffers and textures containing two signed integer channels. </summary>
        Int2                        = GL_RG32I,
        /// <summary> A 96-bit RGB format for color buffers and textures containing three signed integer channels. </summary>
        Int3                        = GL_RGB32I,
        /// <summary> A 128-bit RGBA format for color buffers and textures containing four signed integer channels. </summary>
        Int4                        = GL_RGBA32I,

        Short1                      = GL_R16,
        Short2                      = GL_RG16,
        Short3                      = GL_RGB16,
        Short4                      = GL_RGBA16,

        /// <summary> A 32-bit format for color buffers and textures containing one unsigned integer channel. </summary>
        UInt1                       = GL_R32UI,
        /// <summary> A 64-bit RG format for color buffers and textures containing two unsigned integer channels. </summary>
        UInt2                       = GL_RG32UI,
        /// <summary> A 96-bit RGB format for color buffers and textures containing three unsigned integer channels. </summary>
        UInt3                       = GL_RGB32UI,
        /// <summary> A 128-bit RGBA format for color buffers and textures containing four unsigned integer channels. </summary>
        UInt4                       = GL_RGBA32UI,
    };

    constexpr TextureFormats(enum Formats f = Byte4) : Enumerator((int)f) { }

	/// <summary> Converts specific OpenGL internal format enumerators into their equivalent base format values. </summary>
	/// <remarks>
	///     OpenGL possesses several functions that distinguish between the simpler, base format values such as GL_RGBA and
	///     more specific ones such as GL_RGBA8 (i.e. 8-bits per channel RGBA). However, if the specific internal format is
	///     known, then the base format can also be determined. This method performs that conversion and makes it a bit
	///     easier to automate certain aspects of texture usage.
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
        /// <summary> A one-dimensional texture storage format. </summary>
        Texture1D                   = GL_TEXTURE_1D,
        /// <summary> A two-dimensional texture storage format. </summary>
        Texture2D                   = GL_TEXTURE_2D,

        TextureArray2D              = GL_TEXTURE_2D_ARRAY,
        /// <summary> A multisampled two-dimensional texture storage format. </summary>
        Texture2DMS                 = GL_TEXTURE_2D_MULTISAMPLE,
        /// <summary> A three-dimensional texture storage format. </summary>
        Texture3D                   = GL_TEXTURE_3D,
    };

    constexpr TextureTargets(enum Targets t = Texture2D) : Enumerator((int)t) { }
};

/// <summary> A list of supported topologies that indicate the primitive geometry to be rendered. </summary>
/// <remarks>
///     Topologies describe how collections of vertices should be parsed and rendered on-screen. The enumerators provided here are
///     intended for use in all 'glDraw' API functions as a replacement for clumsier 'GLenum mode' arguments.
///
///     Uninitalized instances of these enumerators default to the value of 'Triangles'.
/// </remarks>
struct VertexTopologies : public Enumerator
{
    enum Topologies
    {
        /// <summary> Instructs the rendering pipeline to draw lines using an array of vertices. </summary>
        Lines                       = GL_LINES,
        LineLoop                    = GL_LINE_LOOP,
        LineStrip                   = GL_LINE_STRIP,
        /// <summary> Instructs the rendering pipeline to draw scalable vector graphics using an array of control points. </summary>
        /// <remarks>
        ///     This is a special enumerator inserted to support the rendering of resolution-independent paths, which is the process used 
        ///     to generate scalable vector graphics (SVGs). Because this is a special format, ordinary OpenGL functions that operate on 
        ///     vertex topologies will not work with this value. 
        /// </remarks>
        Path                        = -1,
        /// <summary> Instructs the rendering pipeline to draw individual points using an array of vertices. </summary>
        Points                      = GL_POINTS,
        Quads                       = GL_QUADS,
        /// <summary> Instructs the rendering pipeline to draw triangles using an array of vertices. </summary>
        Triangles                   = GL_TRIANGLES,
        TriangleFan                 = GL_TRIANGLE_FAN,
        /// <summary> Instructs the rendering pipeline to draw a series of contiguous triangles using an array of vertices. </summary>
        TriangleStrip               = GL_TRIANGLE_STRIP,
    };

    constexpr VertexTopologies(enum Topologies t = Triangles) : Enumerator((int)t) { }
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

        MirrorClampToEdge           = GL_MIRROR_CLAMP_TO_EDGE,
        /// <summary> Wraps out-of-bounds sampling coordinates back across the texture. </summary>
        MirrorRepeat                = GL_MIRRORED_REPEAT,
        /// <summary> Wraps out-of-bounds sampling coordinates to the opposite side of the texture. </summary>
        Repeat                      = GL_REPEAT,
    };

    constexpr WrapModes(enum Modes m = Repeat) : Enumerator((int)m) { }
};

/// <summary> A list of supported modes by which framebuffer changes are synchronized to the computer screen refresh rate. </summary>
struct VSyncModes : public Enumerator
{
	enum Modes
	{
        /// <summary> Synchronizes screen refreshing with the rate at which the framebuffer is updated. </summary>
        /// <remarks>
        ///     This vsync mode is a relatively new innovation that is usually referred to by the trade names 'G-Sync' 
        ///     (on NVIDIA hardware) or 'FreeSync' (on AMD hardware) and currently requires specialized hardware to 
        ///     operate.
        /// </remarks>
		Adaptive                    = -1,
        /// <summary> Disables the synchronization between monitor refreshing and framebuffer updates. </summary>
        /// <remarks>
        ///     Disabling vsync allows updates to the computer monitor and the OpenGL framebuffer to occur completely 
        ///     asynchronously, meaning that the screen is free to refresh at its native rate (usually 60 Hz) and the 
        ///     framebuffer is refreshed as quickly as the GPU can execute the bound rendering pipeline. This mode works 
        ///     best when the process of rendering into a framebuffer occurs more quickly than the native screen refresh 
        ///     rate and no specialized hardware is available to take advantage of adaptive refreshing.
        ///
        ///     However, if the GPU requires more time to render to a framebuffer than the screen takes to refresh (i.e. 
        ///     more than 1/60th of a second), then use of this mode leads to the appearance of an image artifact called 
        ///     'tearing'. Screen tearing occurs when the monitor refreshes what's displayed to the user even though the 
        ///     GPU is not yet finished updating the framebuffer, and the result is a visible image that contains both 
        ///     old and new rendered graphics. If the framebuffer update being processed involves significant changes to 
        ///     the imagery relative to the previous frame, then this phenomenon becomes very noticeable and unpleasant.
        /// </remarks>
		Disable                     = 0,
        /// <summary> Synchronizes framebuffer updates with the rate at which the computer screen is refreshed. </summary>
        /// <remarks>
        ///     Enabling vsync forces framebuffer updates to occur synchronously with the updates to the computer monitor, 
        ///     meaning that the framebuffer can only be refreshed whenever the screen generates a refresh pulse. This 
        ///     mode works best when the process of rendering into a framebuffer is significantly slower than the native 
        ///     screen refresh rate (usually 60 Hz) and no specialized hardware is available to take advantage of adaptive 
        ///     refreshing. In such cases, vsync prevents the appearance of an ugly imaging artifact called 'tearing', which 
        ///     occurs when the screen refreshes in the middle of a framebuffer update and displays both new and outdated 
        ///     graphics to the user.
        /// </remarks>
		Enable                      = 1,
	};

    constexpr VSyncModes(enum Modes m = Enable) : Enumerator((int)m) { }
};


struct WindingOrders : public Enumerator
{
    enum Orders
    {
        None                        = 0,
        Clockwise                   = 1,
        CounterClockwise            = 2,
    };

    constexpr WindingOrders(enum Orders o = None) : Enumerator((int)o) { }
};