/* CHANGELOG
 * Written by Josh Grooms on 20160504
 */

#pragma once
#include "Area.h"
#include "Textures/Texture2D.h"
#include "Vector2.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class OpenGLAPI FrameBuffer
        {

            public:

                /** DATA **/
                /* COLORTEXTURE - The texture currently serving as the color attachment for this framebuffer. */
                Texture2D* ColorTexture;
                /* DEPTHTEXTURE - The texture currently serving as the depth attachment for this framebuffer. */
                Texture2D* DepthTexture;



                /** PROPERTIES **/
                /* DISPLAYAREA - Gets the size and position of this framebuffer in pixels. */
                Area DisplayArea()      const { return Area(0, 0, ColorTexture->Width(), ColorTexture->Height()); }
                /* HEIGHT - Gets the height of this framebuffer in pixels. */
                uint Height()           const { return (uint)_size.Y; }
                /* ID - Gets the numeric handle (or 'Name' in OpenGL jargon) associated with this framebuffer. */
                uint ID()               const { return _id; }
                /* SIZE - Gets the width and height of this framebuffer in pixels. */
                const Vector2& Size()   const { return _size; }
                /* WIDTH - Gets the width of this framebuffer in pixels. */
                uint Width()            const { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /* FRAMEBUFFER - Constructs an empty framebuffer object. */
                FrameBuffer();
                /* FRAMEBUFFER - Constructs a new framebuffer object that can be used to render images.
                 *
                 *      Framebuffers constructed via this method contain both a color buffer and a depth buffer, enabling render-to-
                 *      texture and depth testing.
                 *
                 *      SYNTAX:
                 *          F = FrameBuffer(size)
                 *          F = FrameBuffer(size, colorFormat)
                 *          F = FrameBuffer(size, colorFormat, depthFormat)
                 *
                 *      OUTPUT:
                 *          F:              FrameBuffer
                 *
                 *      INPUTS:
                 *          size:           const Vector2&
                 *                          The desired width and height (in pixels) of the framebuffer, specified respectively as
                 *                          the X and Y components of a two-element vector.
                 *
                 *      OPTIONAL INPUTS:
                 *          colorFormat:    TextureFormats
                 *                          The desired format of the color texture attachment.
                 *                          DEFAULT: TextureFormats::Byte4
                 *
                 *          depthFormat:    TextureFormats
                 *                          The desired format of the depth texture attachment.
                 *                          DEFAULT: TextureFormats::DepthFloat
                 */
                FrameBuffer(const Vector2& size, TextureFormats colorFormat = TextureFormats::Byte4, TextureFormats depthFormat = TextureFormats::DepthFloat);
                /* ~FRAMEBUFFER - Unbinds the framebuffer and destroys all resources that are held by it. */
                ~FrameBuffer();



                /** STATIC CONSTRUCTORS **/
                /* COLORBUFFER - Constructs a framebuffer object containing only a single color buffer attachment.
                 *
                 *      Framebuffers constructed via this method contain only a color buffer attachment; the depth buffer is left as
                 *      a null pointer. This enables render-to-texture functionality but disables depth testing.
                 *
                 *      SYNTAX:
                 *          F = FrameBuffer::ColorBuffer(size)
                 *          F = FrameBuffer::ColorBuffer(size, format)
                 *
                 *      OUTPUT:
                 *          F:          FrameBuffer*
                 *                      A pointer to the newly constructed color-only framebuffer object. The memory used by this
                 *                      object is not automatically managed and must be manually reclaimed.
                 *
                 *      INPUT:
                 *          size:       const Vector2&
                 *                      The desired width and height of the color texture that will be attached to this framebuffer
                 *                      as the X and Y vector coordinates, respectively. Typically, this size would be specified in
                 *                      units of pixels (if the contents will eventually be transferred to the default framebuffer
                 *                      without being scaled), although units could be arbitrary if more advanced manipulations will
                 *                      take place.
                 *
                 *      OPTIONAL INPUT:
                 *          format:     TextureFormats
                 *                      One of the texture format enumerators specifying how much memory gets allocated per texel. By
                 *                      default, color buffers are created with a fixed-point RGBA format utilizing 8 bits of GPU
                 *                      memory per color channel.
                 *                      DEFAULT: TextureFormats::Byte4
                 */
                static FrameBuffer* ColorBuffer(const Vector2& size, TextureFormats format = TextureFormats::Byte4);
                /* DEPTHBUFFER - Constructs a framebuffer object containing only a single depth buffer attachment.
                 *
                 *      Framebuffers constructed via this method contain only a depth buffer attachment; the color buffer is left as
                 *      a null pointer. This enables depth testing functionality but disables the rendering of colors to a texture.
                 *
                 *      SYNTAX:
                 *          F = FrameBuffer::DepthBuffer(size)
                 *          F = FrameBuffer::DepthBuffer(size, format)
                 *
                 *      OUTPUT:
                 *          F:          FrameBuffer
                 *                      A pointer to the newly constructed depth-only framebuffer object. The memory used by this
                 *                      object is not automatically managed and must be manually reclaimed.
                 *
                 *      INPUT:
                 *          size:       const Vector2&
                 *                      The desired width and height of the depth texture that will be attached to this framebuffer
                 *                      as the X and Y vector coordinates, respectively. Typically, this size would be specified in
                 *                      units of pixels (if the contents will eventually be transferred to the default framebuffer
                 *                      without being scaled), although units could be arbitrary if more advanced manipulations will
                 *                      take place.
                 *
                 *      OPTIONAL INPUT:
                 *          format:     TextureFormats
                 *                      One of the texture format enumerators specifying how much memory gets allocated per texel. By
                 *                      default, depth buffers are created with a fixed-point 32-bit float format.
                 *                      DEFAULT: TextureFormats::DepthFloat
                 */
                static FrameBuffer* DepthBuffer(const Vector2& size, TextureFormats format = TextureFormats::DepthFloat);



                /** UTILITIES **/
                /* BIND - Attaches this framebuffer and its associated resources to the GPU. */
                void Bind();
                /* CLEAR - Overwrites all data within each of the textures attached to this framebuffer. */
                void Clear();
                /* REPORT - Generates a human-readable string detailing the current internal state of this object. */
                string Report() const;
                /* UNBIND - Detaches this framebuffer and its associated resources from the GPU. */
                void Unbind();

            private:

                /** PROPERTY DATA **/
                uint        _id;
                Vector2     _size;



                /** PRIVATE UTILITIES **/
                void CreateColorAttachment(TextureFormats format);
                void CreateDepthAttachment(TextureFormats format);
                string ReportCompletionStatus() const;

        };
    }
}