#include "EnumerationsGL.h"
#include "FrameBuffer.h"
#include "OpenGL.h"
#include "Texture2D.h"
#include "Utilities.h"
#include <sstream>


namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        FrameBuffer::FrameBuffer() :
            _id(0),
            ColorTexture(nullptr),
            DepthTexture(nullptr)
        {
            glCreateFramebuffers(1, &_id);
        }
        FrameBuffer::FrameBuffer(const Vector2& size, TextureFormats colorFormat, TextureFormats depthFormat) :
            _id(0),
            _size(size),
            ColorTexture(nullptr),
            DepthTexture(nullptr)
        {
            glCreateFramebuffers(1, &_id);
            CreateColorAttachment(colorFormat);
            CreateDepthAttachment(depthFormat);
        }
        FrameBuffer::~FrameBuffer()
        {
            Unbind();
            if (_id)            { glDeleteFramebuffers(1, &_id); }
            if (DepthTexture)   { delete DepthTexture; }
            if (ColorTexture)   { delete ColorTexture; }
        }



        /** STATIC CONSTRUCTORS **/
        FrameBuffer* FrameBuffer::ColorBuffer(const Vector2& size, TextureFormats format)
        {
            FrameBuffer* cbuffer = new FrameBuffer();
            cbuffer->_size = size;
            cbuffer->CreateColorAttachment(format);
            return cbuffer;
        }
        FrameBuffer* FrameBuffer::DepthBuffer(const Vector2& size, TextureFormats format)
        {
            FrameBuffer* dbuffer = new FrameBuffer();
            dbuffer->_size = size;
            dbuffer->CreateDepthAttachment(format);
            return dbuffer;
        }



        /** PUBLIC UTILITIES **/
        void FrameBuffer::Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _id);
            glViewport(0, 0, Width(), Height());
        }
        void FrameBuffer::Clear()
        {
            const float* white = Color4::White.ToArray();
            if (ColorTexture)
                glClearBufferfv(GL_COLOR, 0, white);

            if (DepthTexture)
                glClearBufferfv(GL_DEPTH, 0, white);
        }
        string FrameBuffer::Report() const
        {
            std::stringstream msg;
            msg << "Framebuffer Description:\n" <<
                   "\tID:                 " << _id                          << "\n" <<
                   "\tStatus:             " << ReportCompletionStatus()     << "\n\n";

            if (ColorTexture)
                msg << "\tFramebuffer Color " << ColorTexture->Report();

            if (DepthTexture)
                msg << "\n\tFramebuffer Depth " << DepthTexture->Report();

            return msg.str();
        }

        void FrameBuffer::Unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }



        /** PRIVATE UTILITIES **/
        void FrameBuffer::CreateColorAttachment(TextureFormats format)
        {
            ColorTexture = new Texture2D(format, Size());
            ColorTexture->Sampler.EdgeWrap = WrapModes::Repeat;

            glNamedFramebufferTexture(_id, GL_COLOR_ATTACHMENT0, ColorTexture->ID(), 0);
            glNamedFramebufferDrawBuffer(_id, GL_COLOR_ATTACHMENT0);
        }
        void FrameBuffer::CreateDepthAttachment(TextureFormats format)
        {
            DepthTexture = new Texture2D(format, Size());
            glNamedFramebufferTexture(_id, GL_DEPTH_ATTACHMENT, DepthTexture->ID(), 0);
        }
        /* REPORTCOMPLETIONSTATUS - Returns a human-readable string describing the completion state of this framebuffer. */
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