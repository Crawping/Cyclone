/* CHANGELOG
 * Written by Josh Grooms on 20160504
 */

#pragma once
#include "Interfaces/IBindable.h"
#include "Spatial/Area.h"
#include "Textures/Texture2D.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer : public virtual IBindable
        {

            public:

                
                /** PROPERTIES **/
                /// <summary> Gets the size and position of this framebuffer in pixels. </summary>
                Area DisplayArea()      const { return Area(0, 0, ColorTexture->Width(), ColorTexture->Height()); }
                /// <summary> Gets the height of this framebuffer in pixels. </summary>
                uint Height()           const { return (uint)_size.Y; }
                /// <summary> Gets the numeric handle (or 'Name' in OpenGL jargon) associated with this framebuffer. </summary>
                uint ID()               const override { return _id; }
                /// <summary> Gets the width and height of this framebuffer in pixels. </summary>
                const Vector3& Size()   const { return (Vector3)_size; }

                TextureTargets Target() const { return _target; }
                /// <summary> Gets the width of this framebuffer in pixels. </summary>
                uint Width()            const { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs an empty framebuffer object with no attachments. </summary>
                OpenGLAPI FrameBuffer();

                OpenGLAPI FrameBuffer(FrameBuffer&& other);
                /// <summary> Constructs a new framebuffer object that can be used to render images. </summary>
                /// <param name="size">
                ///     The (x, y, z, w) size of the texture objects that comprise the framebuffer. 
                ///     <para> </para>
                ///     Texture size is specified as a four-element vector containing width, height, depth, 
                ///     and count values, in that order. If a multisampled texture is being requested, then 
                ///     the vector's 'W' component is interpretted as the sample count. Otherwise, this value 
                ///     is interpretted as the mipmap level count for the texture's storage.
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
                OpenGLAPI FrameBuffer(const Vector4& size, TextureFormats colorFormat = TextureFormats::Byte4, TextureFormats depthFormat = TextureFormats::DepthFloat);

                OpenGLAPI FrameBuffer(const Vector4& size, TextureFormats colorFormat, TextureFormats depthFormat, TextureTargets target);
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
                static OpenGLAPI FrameBuffer* ColorBuffer(const Vector4& size, TextureFormats format = TextureFormats::Byte4);
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
                static OpenGLAPI FrameBuffer* DepthBuffer(const Vector4& size, TextureFormats format = TextureFormats::DepthFloat);



                /** BINDING UTILITIES **/
                /// <summary> Summarily attaches this framebuffer and its associated resources to the GPU. </summary>
                /// <param name="slot"> A parameter of the <see cref="IBindable"/> interface that has no effects here. </param>
                OpenGLAPI void Bind(int slot = 0)       const override;
                /// <summary> Attaches this framebuffer object to the GPU. </summary>
                /// <param name="slot"> A parameter of the <see cref="IBindable"/> interface that has no effects here. </param>
                OpenGLAPI void BindEntity(int slot = 0) const override;
                /// <summary> Attaches any secondary resources associated with this framebuffer to the GPU. </summary>
                /// <remarks> This method is part of the <see cref="IBindable"/> interface but has no effects here. </remarks>
                OpenGLAPI void BindResources()          const override { }
                /// <summary> Summarily detaches this framebuffer and its associated resources from the GPU. </summary>
                OpenGLAPI void Unbind()                 const override;
                /// <summary> Detaches this framebuffer object from the GPU. </summary>
                OpenGLAPI void UnbindEntity()           const override;
                /// <summary> Detaches any secondary resources associated with this framebuffer from the GPU. </summary>
                /// <remarks> This method is part of the <see cref="IBindable"/> interface but has no effects here. </remarks>
                OpenGLAPI void UnbindResources()        const override { }



                /** UTILITIES **/
                /// <summary> Copies a data subset from this framebuffer to another one. </summary>
                /// <param name="target">
                ///     A pointer to the target or destination framebuffer of the copy operation. If this value is <c>NULL</c> or 
                ///     a <c>nullptr</c>, then the target will be the default framebuffer of the rendering window (i.e. the one 
                ///     provided by the operating system).
                /// </param>
                /// <param name="srcArea"> The rectangular region of this framebuffer to be copied. </param>
                /// <param name="dstArea"> The rectangular region of the target framebuffer where data will be written. </param>
                OpenGLAPI void Blit(FrameBuffer* target, const Area& srcArea, const Area& dstArea) const;
                /// <summary> Overwrites all data within each of the textures attached to this framebuffer. </summary>
                /// <param name="color"> The color value to which all attached color buffers will be reset. </param>
                /// <param name="depth"> The value to which the attached depth buffer will be reset. </param>
                /// <param name="stencil"> The value to which the attached stencil buffer will be reset. </param>
                OpenGLAPI void Clear(const Color4& color = Color4::White, float depth = 1.0f, int stencil = 0);
                /// <summary> Generates a human-readable string detailing the current internal state of this object. </summary>
                OpenGLAPI string Report()   const;
                
                

            private:

                /** PROPERTY DATA **/
                uint            _id;
                Vector4         _size;
                TextureTargets  _target;



                /** DATA **/
                /// <summary> The texture currently serving as the color attachment for this framebuffer. </summary>
                Texture2D* ColorTexture;
                /// <summary> The texture currently serving as the depth attachment for this framebuffer. </summary>
                Texture2D* DepthTexture;



                /** PRIVATE UTILITIES **/
                void CreateColorAttachment(TextureFormats format, TextureTargets target);
                void CreateDepthAttachment(TextureFormats format, TextureTargets target);
                bool HasStencilBuffer() const;
                string ReportCompletionStatus() const;

        };
    }
}