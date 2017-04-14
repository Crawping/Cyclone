#include "Console.h"
#include "Utilities.h"
#include "Textures/Texture3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        Texture3D& Texture3D::BorderColor(const Color4& value)
        {
            _sampler.BorderColor(value);
            return *this;
        }
        Texture3D& Texture3D::EdgeWrap(WrapModes value)
        {
            _sampler.EdgeWrap(value);
            return *this;
        }
        Texture3D& Texture3D::LOD(int value)
        {
            _sampler.LOD(value);
            return *this;
        }
        Texture3D& Texture3D::MagnifyFilter(TextureFilters value)
        {
            _sampler.MagnifyFilter(value);
            return *this;
        }
        Texture3D& Texture3D::MaxLOD(int value)
        {
            _sampler.MaxLOD(value);
            return *this;
        }
        Texture3D& Texture3D::MinifyFilter(TextureFilters value)
        {
            _sampler.MinifyFilter(value);
            return *this;
        }
        Texture3D& Texture3D::MinLOD(int value)
        {
            _sampler.MinLOD(value);
            return *this;
        }
        Texture3D& Texture3D::Sampler(const TextureSampler& value)
        {
            return 
                 BorderColor(value.BorderColor())
                .EdgeWrap(value.EdgeWrap())
                .LOD(value.LOD())
                .MagnifyFilter(value.MagnifyFilter())
                .MaxLOD(value.MaxLOD())
                .MinifyFilter(value.MinifyFilter())
                .MinLOD(value.MinLOD());
        }
        Texture3D& Texture3D::Size(const Vector4& value)
        {
            if (value == Size()) { return *this; }

            _size = Vector4(value.X, value.Y, value.Z, Math::Max(value.W, 1.0f));
            _needsUpdate = true;
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Texture3D::Texture3D() :
            _handle(0),
            _id(0),
            _isResident(false),
            _needsUpdate(false)
        {

        }
        Texture3D::Texture3D(Texture3D&& other) :
            _format(other._format),
            _handle(other._handle),
            _id(other._id),
            _isResident(other._isResident),
            _needsUpdate(other._needsUpdate),
            _size(other._size),
            _target(other._target)
        {
            other._handle = 0;
            other._id = 0;
            std::swap(_sampler, other._sampler);
        }
        Texture3D::Texture3D(const Vector4& size, TextureFormats format, TextureTargets target) :
            _format(format),
            _handle(0),
            _id(0),
            _isResident(false),
            _needsUpdate(true),
            _size(size),
            _target(target)
        {
            _size.X = Math::Max(_size.X, 1.0f);
            _size.Y = Math::Max(_size.Y, 1.0f);
            _size.Z = Math::Max(_size.Z, 1.0f);
            _size.W = Math::Max(_size.W, 1.0f);
        }
        Texture3D::~Texture3D()
        {
            MakeNonresident();
            if (_id)
                glDeleteTextures(1, &_id);
        }



        /** BINDING UTILITIES **/
        void Texture3D::Bind(int slot)          const
        {
            BindEntity(slot);
            BindResources();
        }
        void Texture3D::BindEntity(int slot)    const
        {
            glBindTextureUnit(slot, ID());
        }
        void Texture3D::BindResources()         const
        {
            _sampler.Bind();
        }

        void Texture3D::Unbind()                const
        {
            UnbindResources();
            UnbindEntity();
        }
        void Texture3D::UnbindEntity()          const
        {

        }
        void Texture3D::UnbindResources()       const 
        {
            _sampler.Unbind();
        }



        /** TEXTURE UTILITIES **/
        void Texture3D::GenerateMipmap()
        {
            if ( IsEmpty() || !MipmapCount() || (Target() == TextureTargets::Texture2DMS) )
                return;

            Update();
            glGenerateTextureMipmap(ID());
        }
        void Texture3D::MakeNonresident()
        {
            if (!IsResident()) { return; }
            glMakeTextureHandleNonResidentARB(Handle());
            _isResident = false;
        }
        void Texture3D::MakeResident()
        {
            Update();
            if (!_handle)
                _handle = glGetTextureSamplerHandleARB(_id, _sampler.ID());
            glMakeTextureHandleResidentARB(Handle());
            _isResident = true;
        }
        void Texture3D::Update()
        {
            _sampler.Update();
            if (!NeedsUpdate()) { return; }
            Reallocate();
            _needsUpdate = false;
        }



        /** PROTECTED UTILITIES **/
        void Texture3D::Allocate()
        {
            switch (Target())
            {
                case TextureTargets::Texture1D:
                    glTextureStorage1D(ID(), MipmapCount(), Format(), (int)Width());
                    break;
                case TextureTargets::Texture2D:
                    glTextureStorage2D(ID(), MipmapCount(), Format(), (int)Width(), (int)Height());
                    break;
                case TextureTargets::Texture2DMS:
                    glTextureStorage2DMultisample(ID(), SampleCount(), Format(), (int)Width(), (int)Height(), true);
                    break;

                case TextureTargets::Texture3D:
                case TextureTargets::TextureArray2D:
                    glTextureStorage3D(ID(), MipmapCount(), Format(), (int)Width(), (int)Height(), (int)Depth());
                    break;
            }
        }
        void Texture3D::Create()
        {
            if (_id)
            {
                Console::WriteLine("A texture object already exists and must be deleted before attempting to create a new one.");
                return;
            }
            glCreateTextures(Target(), 1, &_id);
        }
        void Texture3D::Destroy()
        {
            if (_id)
            {
                MakeNonresident();
                glDeleteTextures(1, &_id);
                _handle = 0;
                _id = 0;
            }
        }
        void Texture3D::Reallocate()
        {
            Destroy();
            Create();
            Allocate();
        }



        /** OPERATORS **/
        Texture3D& Texture3D::operator =(Texture3D&& other)
        {
            _format         = other._format;
            _handle         = other._handle;
            _id             = other._id;
            _needsUpdate    = other._needsUpdate;
            _size           = other._size;
            _target         = other._target;

            other._id = 0;
            other._handle = 0;
            other._needsUpdate = false;
            std::swap(_sampler, other._sampler);

            return *this;
        }

    }
}
