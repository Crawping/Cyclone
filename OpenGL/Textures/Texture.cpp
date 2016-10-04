#include "Console.h"
#include "Texture.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        /** PROPERTIES **/
        Texture& Texture::Format(TextureFormats value)
        {
            if (value != _format)
            {
                _format = value;
                _needsUpdate = true;
            }
            return *this;
        }
        Texture& Texture::MipmapCount(uint value)
        {
            if (value != _mipmapCount)
            {
                _mipmapCount = value;
                _needsUpdate = true;
            }
            return *this;
        }
        Texture& Texture::Size(const Vector3& value)
        {
            if (value != _size)
            {
                _size = value;
                _needsUpdate = true;
            }
            return *this;
        }
        Texture& Texture::Target(TextureTargets value)
        {
            if (value != _target)
            {
                _target = value;
                _needsUpdate = true;
            }
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Texture::Texture() :
            _handle(0),
            _id(0),
            _mipmapCount(4),
            _needsUpdate(true)
        {

        }
            
        Texture::Texture(const Vector3& size, TextureFormats format, TextureTargets target) :
            _format(format),
            _handle(0),
            _id(0),
            _mipmapCount(4),
            _needsUpdate(true),
            _size(size),
            _target(target)
        {
            
        }
        Texture::~Texture()
        {
            //MakeNonresident();
            if (_id)
                glDeleteTextures(1, &_id);
        }



        /** BINDING UTILITIES **/
        void Texture::BindEntity(int slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(Target(), ID());
        }
        void Texture::MakeNonresident()
        {
            glMakeTextureHandleNonResidentARB(Handle());
        }
        void Texture::MakeResident()
        {
            if (!_handle)
                _handle = glGetTextureHandleARB(_id);
            glMakeTextureHandleResidentARB(Handle());
        }
        void Texture::UnbindEntity() const
        {
            glBindTexture(Target(), 0);
            glActiveTexture(GL_TEXTURE0);
        }



        /** TEXTURE UTILITIES **/
        void Texture::GenerateMipmap()
        {
            if (IsEmpty()) { return; }
            glGenerateTextureMipmap(ID());
        }
        void Texture::Update()
        {
            if (!NeedsUpdate()) { return; }

            Reallocate();
            _needsUpdate = false;
        }



        /** PROTECTED UTILITIES **/
        void Texture::Allocate()
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
                    glTextureStorage2DMultisample(ID(), 4, Format(), (int)Width(), (int)Height(), true);
                    break;
                case TextureTargets::Texture3D:
                    glTextureStorage3D(ID(), MipmapCount(), Format(), (int)Width(), (int)Height(), (int)Depth());
                    break;
            }
        }

        void Texture::Create()
        {
            if (_id)
            {
                Console::WriteLine("A texture object already exists and must be deleted before attempting to create a new one.");
                return;
            }
            glCreateTextures(Target(), 1, &_id);
        }
        void Texture::Destroy()
        {
            if (_id)
            {
                //MakeNonresident();
                glDeleteTextures(1, &_id);
                _handle = 0;
                _id = 0;
            }
        }
        void Texture::Reallocate()
        {
            Destroy();
            Create();
            Allocate();
        }
    }
}