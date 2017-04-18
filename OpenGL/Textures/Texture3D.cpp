#include "Console.h"
#include "Utilities.h"
#include "Imaging/Bitmap.h"
#include "Spatial/Volume.h"
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
            _needsUpdate(false),
            _ownsResource(true)
        {

        }
        Texture3D::Texture3D(Texture3D&& other) :
            _format(other._format),
            _handle(other._handle),
            _id(other._id),
            _isResident(other._isResident),
            _needsUpdate(other._needsUpdate),
            _ownsResource(other._ownsResource),
            _size(other._size),
            _target(other._target)
        {
            other._handle = 0;
            other._id = 0;
            std::swap(_sampler, other._sampler);
        }
        Texture3D::Texture3D(const Texture3D& other) :
            _format(other._format),
            _handle(0),
            _id(other._id),
            _isResident(false),
            _needsUpdate(true),
            _ownsResource(false),
            _sampler(other._sampler),
            _size(other._size),
            _target(other._target)
        {

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
            if (_id && _ownsResource)
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



        /** IMAGING UTILITIES **/
        void Texture3D::Blit(ITexture& target, const Volume& src, int srcLevel, const Volume& dst, int dstLevel) const
        {
            glCopyImageSubData
            (
                ID(),
                Target(),
                srcLevel, src.X, src.Y, src.Z,
                target.ID(),
                target.Target(),
                dstLevel, dst.X, dst.Y, dst.Z,
                src.Width, src.Height, src.Depth
            );
        }
        Texture3D* Texture3D::CreateView()                      const
        {
            return new Texture3D(*this);
        }
        void Texture3D::Fill(const Color4& value)
        {
            glClearTexSubImage
            (
                ID(),
                0, 0, 0, 0, 
                Width(), Height(), Depth(), 
                Format().ToBaseFormat(),
                NumericFormats::Float,
                value.ToArray()
            );
        }
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
        Bitmap Texture3D::Read(const Volume& region, int level) const
        {
            Vector3 size(region.Size());
            Bitmap bmp(size);

            glGetTextureSubImage
            (
                ID(),
                level,
                region.X,   region.Y,   region.Z,
                size.X,     size.Y,     size.Z,
                Format().ToBaseFormat(),
                NumericFormats::Float,
                bmp.Count() * sizeof(Color4),
                bmp.ToArray()
            );
            return bmp;
        }
        void Texture3D::Update()
        {
            _sampler.Update();
            if (!_needsUpdate) { return; }
            Reallocate();
            _needsUpdate = false;
        }
        void Texture3D::Write(const Bitmap& values)
        {
            Write(0, Volume(Vector3::Zero, values.Size()), values);
        }
        void Texture3D::Write(int level, const Volume& region, const Bitmap& values)
        {
            glTextureSubImage2D
            (
                ID(), 
                level, region.X, region.Y, 
                region.Width, region.Height, 
                Format().ToBaseFormat(), 
                NumericFormats::Float, 
                values.ToArray()
            );
        }
        


        /** PROTECTED UTILITIES **/
        void Texture3D::Allocate()
        {
            if (!_id)
                return Console::WriteLine("Texture resources must have existing names on the GPU before storage space can be allocated.");
            else if (!_ownsResource)
                return Console::WriteLine("Resource views are not allowed to reallocate their underlying storage spaces.");

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
                return Console::WriteLine("Existing texture resources must be destroyed before attempting to recreate them.");

            glCreateTextures(Target(), 1, &_id);
        }
        void Texture3D::Destroy()
        {
            if (!_ownsResource)
                return Console::WriteLine("Resource views are not allowed to destroy their underlying GPU objects.");

            if (_id && _ownsResource)
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
