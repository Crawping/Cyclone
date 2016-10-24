#include "Console.h"
#include "Texture.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        /** PROPERTIES **/
        Texture3D& Texture3D::Format(TextureFormats value)
        {
            if (value == Format()) { return *this; }
            _format = value;
            _needsUpdate = true;
            return *this;
        }
        Texture3D& Texture3D::MipmapCount(uint value)
        {
            if (value == MipmapCount()) { return *this; }
            _mipmapCount = value;
            _needsUpdate = true;
            return *this;
        }
        Texture3D& Texture3D::Size(const Vector3& value)
        {
            if (value == Size()) { return *this; }
            _size = value;
            _needsUpdate = true;
            return *this;
        }
        Texture3D& Texture3D::Target(TextureTargets value)
        {
            if (value == Target())
            _target = value;
            _needsUpdate = true;
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Texture3D::Texture3D() :
            _handle(0),
            _id(0),
            _mipmapCount(4),
            _needsUpdate(true)
        {

        }            
        Texture3D::Texture3D(const Vector3& size, TextureFormats format, TextureTargets target) :
            _format(format),
            _handle(0),
            _id(0),
            _mipmapCount(4),
            _needsUpdate(true),
            _size(size),
            _target(target)
        {
            
        }
        Texture3D::~Texture3D()
        {
            //MakeNonresident();
            if (_id)
                glDeleteTextures(1, &_id);
        }



        /** BINDING UTILITIES **/
        void Texture3D::BindEntity(int slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(Target(), ID());
        }
        void Texture3D::MakeNonresident()
        {
            glMakeTextureHandleNonResidentARB(Handle());
        }
        void Texture3D::MakeResident()
        {
            Update();

            if (!_handle)
                _handle = glGetTextureHandleARB(_id);
            glMakeTextureHandleResidentARB(Handle());
        }
        void Texture3D::UnbindEntity() const
        {
            glBindTexture(Target(), 0);
            glActiveTexture(GL_TEXTURE0);
        }



        /** TEXTURE UTILITIES **/
        void Texture3D::GenerateMipmap()
        {
            if ( IsEmpty() || !MipmapCount() || (Target() == TextureTargets::Texture2DMS) ) 
                return;

            Update();
            glGenerateTextureMipmap(ID());
        }
        void Texture3D::Update()
        {
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
                    glTextureStorage2DMultisample(ID(), 4, Format(), (int)Width(), (int)Height(), true);
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
                //MakeNonresident();
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
    }
}