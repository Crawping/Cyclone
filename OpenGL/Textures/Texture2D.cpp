#include "Bitmap.h"
#include "Border.h"
#include "Console.h"
#include "Texture2D.h"
#include "Utilities.h"
#include "Vector3.h"
#include <sstream>



namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTORS & DESTRUCTOR **/
        Texture2D::Texture2D(TextureFormats format, const Vector2& size) :
            Texture(format, TextureTargets::Texture2D),
            _size(size),
            Tint(Color4::White)
        {
            Allocate();
        }



        /** UTILITIES **/
        void Texture2D::Allocate()
        {
            glTextureStorage2D(ID(), 5, Format(), (int)Width(), (int)Height());
        }
        void Texture2D::BindResources() const
        {
            Sampler.Bind();
        }
        void Texture2D::Copy(const Texture2D& texture)
        {
            Sampler = texture.Sampler;
            if (texture.Size() != Size())
            {
                _size = texture.Size();
                Reallocate();
            }

            glCopyImageSubData
            (
                texture.ID(), 
                texture.Target(), 
                0, 0, 0, 0, 
                ID(), 
                Target(), 
                0, 0, 0, 0, 
                Width(), Height(), 1
            );
        }
        void Texture2D::CopyFramebuffer(const Area &screenArea, int level)
        {
            glCopyTextureSubImage2D
            (
                ID(), 
                level, 
                0, 0, 
                (int)screenArea.X, (int)screenArea.Y, 
                screenArea.Width, screenArea.Height
            );
        }
        Bitmap Texture2D::Read(const Vector3& offset, const Vector2& size) const
        {
            Bitmap bmp(size);
            glGetTextureSubImage
            (
                ID(),
                offset.Z,
                offset.X,   offset.Y,   0,
                size.X,     size.Y,     1,
                Format().ToBaseFormat(),
                GL_FLOAT,
                bmp.Length() * sizeof(Color4),
                (void*)bmp.ToArray()
            );
            return bmp;
        }
        string Texture2D::Report() const
        {
            std::stringstream msg;
            msg << "Texture Description:\n\n"                   <<
                   "ID:         " << ID()           << "\n"     <<
                   "Width:      " << Width()        << "\n"     <<
                   "Height:     " << Height()       << "\n";

            return msg.str();
        }
    }
}