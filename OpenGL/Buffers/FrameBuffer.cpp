#include "EnumerationsGL.h"
#include "Buffers/FrameBuffer.h"
#include "GL/OpenGL.h"
#include "Textures/Texture2D.h"
#include "Utilities.h"
#include <sstream>


namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        FrameBuffer::FrameBuffer() :
            _id(0),
            _colorTexture(nullptr),
            _depthTexture(nullptr)
        {
            glCreateFramebuffers(1, &_id);
        }
        FrameBuffer::FrameBuffer(FrameBuffer&& other) :
            _id(other._id),
            _size(other._size),
            _colorTexture(other._colorTexture),
            _depthTexture(other._depthTexture)
        {
            other._id = 0;
            other._size = Vector4::Zero;
            other._colorTexture = nullptr;
            other._depthTexture = nullptr;
        }
        FrameBuffer::FrameBuffer(const Vector4& size, TextureFormats colorFormat, TextureFormats depthFormat) :
            _id(0),
            _size(size),
            _colorTexture(nullptr),
            _depthTexture(nullptr)
        {
            glCreateFramebuffers(1, &_id);
            CreateColorAttachment(colorFormat, TextureTargets::Texture2D);
            CreateDepthAttachment(depthFormat, TextureTargets::Texture2D);
        }
        FrameBuffer::FrameBuffer(const Vector4& size, TextureFormats colorFormat, TextureFormats depthFormat, TextureTargets target) :
            _id(0),
            _size(size),
            _target(target),
            _colorTexture(nullptr),
            _depthTexture(nullptr)
        {
            glCreateFramebuffers(1, &_id);
            CreateColorAttachment(colorFormat, target);
            CreateDepthAttachment(depthFormat, target);
        }
        FrameBuffer::~FrameBuffer()
        {
            Unbind();
            if (_id)            { glDeleteFramebuffers(1, &_id); }
            if (_depthTexture)   { delete _depthTexture; }
            if (_colorTexture)   { delete _colorTexture; }
        }



        /** STATIC CONSTRUCTORS **/
        FrameBuffer* FrameBuffer::ColorBuffer(const Vector4& size, TextureFormats format)
        {
            FrameBuffer* cbuffer = new FrameBuffer();
            cbuffer->_size = size;
            cbuffer->CreateColorAttachment(format, TextureTargets::Texture2D);
            return cbuffer;
        }
        FrameBuffer* FrameBuffer::DepthBuffer(const Vector4& size, TextureFormats format)
        {
            FrameBuffer* dbuffer = new FrameBuffer();
            dbuffer->_size = size;
            dbuffer->CreateDepthAttachment(format, TextureTargets::Texture2D);
            return dbuffer;
        }



        /** PUBLIC UTILITIES **/
        void FrameBuffer::Bind(int slot) const
        {
            BindEntity(slot);
        }
        void FrameBuffer::BindEntity(int slot) const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _id);
        }
        void FrameBuffer::Blit(FrameBuffer* target, const Area& srcArea, const Area& dstArea) const
        {
            glBlitNamedFramebuffer
            (
                ID(),
                target ? target->ID() : 0,
                srcArea.X, srcArea.Y, srcArea.Width, srcArea.Height,
                dstArea.X, dstArea.Y, dstArea.Width, dstArea.Height,
                GL_COLOR_BUFFER_BIT | ( _depthTexture ? GL_DEPTH_BUFFER_BIT : 0 ),
                GL_NEAREST
            );
        }
        void FrameBuffer::Clear(const Color4& color, float depth, int stencil)
        {
            if (_colorTexture)
                glClearNamedFramebufferfv(ID(), GL_COLOR, 0, color.ToArray());

            if (_depthTexture)
            {
                if (HasStencilBuffer())
                    glClearNamedFramebufferfi(ID(), GL_DEPTH_STENCIL, 0, depth, stencil);
                else
                    glClearNamedFramebufferfv(ID(), GL_DEPTH, 0, &depth);
            }
        }
        string FrameBuffer::Report() const
        {
            std::stringstream msg;
            msg << "Framebuffer Description:"                               << "\n" <<
                   "\tID:                 " << _id                          << "\n" <<
                   "\tStatus:             " << ReportCompletionStatus()     << "\n\n";

            if (_colorTexture)
                msg << "\tFramebuffer Color " << _colorTexture->Report();

            if (_depthTexture)
                msg << "\n\tFramebuffer Depth " << _depthTexture->Report();

            return msg.str();
        }
        void FrameBuffer::Unbind() const
        {
            UnbindEntity();
        }
        void FrameBuffer::UnbindEntity() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }



        /** PRIVATE UTILITIES **/
        void FrameBuffer::CreateColorAttachment(TextureFormats format, TextureTargets target)
        {
            _colorTexture = new Texture2D(_size, format, target);
            _colorTexture->Sampler.EdgeWrap = WrapModes::Repeat;

            glNamedFramebufferTexture(_id, GL_COLOR_ATTACHMENT0, _colorTexture->ID(), 0);
            glNamedFramebufferDrawBuffer(_id, GL_COLOR_ATTACHMENT0);
        }
        void FrameBuffer::CreateDepthAttachment(TextureFormats format, TextureTargets target)
        {
            _depthTexture = new Texture2D(_size, format, target);
            if (HasStencilBuffer())
                glNamedFramebufferTexture(ID(), GL_DEPTH_STENCIL_ATTACHMENT, _depthTexture->ID(), 0);
            else
                glNamedFramebufferTexture(ID(), GL_DEPTH_ATTACHMENT, _depthTexture->ID(), 0);
        }
        bool FrameBuffer::HasStencilBuffer() const
        {
            if (_depthTexture)
                return _depthTexture->Format() == TextureFormats::DepthStencil ||
                    _depthTexture->Format() == TextureFormats::DepthStencilFloat;
            else
                return false;
        }
        /// <summary> Returns a human-readable string describing the completion state of this framebuffer. </summary>
        string FrameBuffer::ReportCompletionStatus() const
        {
            GLenum fboStatus = glCheckNamedFramebufferStatus(_id, GL_FRAMEBUFFER);
            switch (fboStatus)
            {
                case GL_FRAMEBUFFER_COMPLETE:                       return "Framebuffer is complete and ready to use.";
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:          return "Framebuffer has an incomplete attachment.";
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:  return "Framebuffer has a missing or incomplete attachment.";
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:         return "Framebuffer has an incomplete draw buffer.";
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:         return "Framebuffer has an incomplete read buffer.";
                case GL_FRAMEBUFFER_UNSUPPORTED:                    return "Framebuffer has an unsupported internal format.";
                default:                                            return "Framebuffer has an unknown problem.";
            }
        }
    }
}
