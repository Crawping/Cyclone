/* CHANGELOG
 * Written by Josh Grooms on 20160504
 */

#pragma once
#include "Spatial/Area.h"
#include "Textures/Texture2D.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer
        {

            public:

                /** DATA **/
                /// <summary> The texture currently serving as the color attachment for this framebuffer. </summary>
                Texture2D* ColorTexture;
                /// <summary> The texture currently serving as the depth attachment for this framebuffer. </summary>
                Texture2D* DepthTexture;



                /** PROPERTIES **/
                /// <summary> Gets the size and position of this framebuffer in pixels. </summary>
                Area DisplayArea()      const { return Area(0, 0, ColorTexture->Width(), ColorTexture->Height()); }
                /// <summary> Gets the height of this framebuffer in pixels. </summary>
                uint Height()           const { return (uint)_size.Y; }
                /// <summary> Gets the numeric handle (or 'Name' in OpenGL jargon) associated with this framebuffer. </summary>
                uint ID()               const { return _id; }
                /// <summary> Gets the width and height of this framebuffer in pixels. </summary>
                const Vector2& Size()   const { return _size; }
                /// <summary> Gets the width of this framebuffer in pixels. </summary>
                uint Width()            const { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs an empty framebuffer object. </summary>
                OpenGLAPI FrameBuffer();
                /// <summary> Constructs a new framebuffer object that can be used to render images. </summary>
                /// <param name="size">
                ///     The desired width and height (in pixels) of the framebuffer, specified respectively as
                ///     the X and Y components of a two-element vector.
                /// </param>
                /// <param name="colorFormat">
                ///     The desired format of the color texture attachment.
                /// 
                ///     DEFAULT: TextureFormats::Byte4
                /// </param>
                /// <param name="depthFormat">
                ///     The desired format of the depth texture attachment.
                /// 
                ///     DEFAULT: TextureFormats::DepthFloat
                /// </param>
                /// <returns></returns>
                OpenGLAPI FrameBuffer(const Vector2& size, TextureFormats colorFormat = TextureFormats::Byte4, TextureFormats depthFormat = TextureFormats::DepthFloat);
                /// <summary> Unbinds the framebuffer and destroys all resources that are held by it. </summary>
                OpenGLAPI ~FrameBuffer();



                /** STATIC CONSTRUCTORS **/
                /// <summary> Constructs a framebuffer object containing only a single color buffer attachment. </summary>
                /// <param name="size">
                ///     The desired width and height of the color texture that will be attached to this framebuffer
                ///     as the X and Y vector coordinates, respectively. Typically, this size would be specified in
                ///     units of pixels (if the contents will eventually be transferred to the default framebuffer
                ///     without being scaled), although units could be arbitrary if more advanced manipulations will
                ///     take place.
                /// </param>
                /// <param name="format">
                ///     One of the texture format enumerators specifying how much memory gets allocated per texel. By
                ///     default, color buffers are created with a fixed-point RGBA format utilizing 8 bits of GPU
                ///     memory per color channel.
                /// 
                ///     DEFAULT: TextureFormats::Byte4
                /// </param>
                /// <returns>
                ///     A pointer to the newly constructed color-only framebuffer object. The memory used by this
                ///     object is not automatically managed and must be manually reclaimed.
                /// </returns>
                /// <remarks>
                ///     Framebuffers constructed via this method contain only a color buffer attachment; the depth buffer is left as
                ///     a null pointer. This enables render-to-texture functionality but disables depth testing.
                /// </remarks>
                static OpenGLAPI FrameBuffer* ColorBuffer(const Vector2& size, TextureFormats format = TextureFormats::Byte4);
                /// <summary> Constructs a framebuffer object containing only a single depth buffer attachment. </summary>
                /// <param name="size">
                ///     The desired width and height of the depth texture that will be attached to this framebuffer
                ///     as the X and Y vector coordinates, respectively. Typically, this size would be specified in
                ///     units of pixels (if the contents will eventually be transferred to the default framebuffer
                ///     without being scaled), although units could be arbitrary if more advanced manipulations will
                ///     take place. 
                /// </param>
                /// <param name="format">
                ///     One of the texture format enumerators specifying how much memory gets allocated per texel. By
                ///     default, depth buffers are created with a fixed-point 32-bit float format.
                ///
                ///     DEFAULT: TextureFormats::DepthFloat
                /// </param>
                /// <returns>
                ///     A pointer to the newly constructed depth-only framebuffer object. The memory used by this
                ///     object is not automatically managed and must be manually reclaimed.
                /// </returns>
                /// <remarks>
                ///     Framebuffers constructed via this method contain only a depth buffer attachment; the color buffer is left as
                ///     a null pointer. This enables depth testing functionality but disables the rendering of colors to a texture.
                /// </remarks>
                static OpenGLAPI FrameBuffer* DepthBuffer(const Vector2& size, TextureFormats format = TextureFormats::DepthFloat);



                /** UTILITIES **/
                /// <summary> Attaches this framebuffer and its associated resources to the GPU. </summary>
                OpenGLAPI void Bind();
                /// <summary> Overwrites all data within each of the textures attached to this framebuffer. </summary>
                OpenGLAPI void Clear();
                /// <summary> Generates a human-readable string detailing the current internal state of this object. </summary>
                OpenGLAPI string Report() const;
                /// <summary> Detaches this framebuffer and its associated resources from the GPU. </summary>
                OpenGLAPI void Unbind();

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