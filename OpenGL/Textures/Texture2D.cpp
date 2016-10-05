#include "Bitmap.h"
#include "Border.h"
#include "Console.h"
#include "Texture2D.h"
#include "Utilities.h"
#include "Vector3.h"

#include <sstream>
#include <jpeglib.h>



namespace Cyclone
{
    namespace OpenGL
    {

        struct ErrorManagerJPEG
        {
            jpeg_error_mgr  Fields;
            jmp_buf         SetJMPBuffer;
        };

        METHODDEF(void) ErrorExit(j_common_ptr imgInfo)
        {
            ErrorManagerJPEG* err = (ErrorManagerJPEG*)imgInfo->err;
            (*imgInfo->err->output_message)(imgInfo);
            longjmp(err->SetJMPBuffer, 1);
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Texture2D::Texture2D(const Vector2& size, TextureFormats format, TextureTargets target) :
            Texture(size, format, target),
            Tint(Color4::White)
        {
            Update();
        }

        Texture2D::Texture2D(const string& fileName)
        {            
            jpeg_decompress_struct jpgInfo;
            FILE* jpgFile;

            if (!(jpgFile = fopen(fileName.c_str(), "rb")))
            {
                PostInfo("Failed to open the image file " + fileName);
                return;
            }

            ErrorManagerJPEG err;
            jpgInfo.err = jpeg_std_error(&err.Fields);
            err.Fields.error_exit = ErrorExit;

            if (setjmp(err.SetJMPBuffer))
            {
                jpeg_destroy_decompress(&jpgInfo);
                fclose(jpgFile);
                return;
            }

            jpeg_create_decompress(&jpgInfo);
            jpeg_stdio_src(&jpgInfo, jpgFile);
            jpeg_read_header(&jpgInfo, true);
            jpeg_start_decompress(&jpgInfo);

            Vector2 jpgSize(jpgInfo.output_width, jpgInfo.output_height);
            Size(Vector2( min(jpgSize.X, 16384), min(jpgSize.Y, 16384) ));
            Update();

            int rowStride = jpgSize.X * jpgInfo.output_components;
            ubyte* rowBuffer  = new ubyte[rowStride];

            while (jpgInfo.output_scanline < Height())
            {
                uint sline = jpgInfo.output_scanline;
                jpeg_read_scanlines(&jpgInfo, &rowBuffer, 1);
                glTextureSubImage2D(ID(), 0, 0, sline, Width(), 1, GL_RGB, NumericFormats::UByte, rowBuffer);
            }

            delete[] rowBuffer;

            jpeg_destroy_decompress(&jpgInfo);
            fclose(jpgFile);
        }
                


        /** UTILITIES **/
        void Texture2D::BindResources() const
        {
            Sampler.Bind();
        }
        void Texture2D::Copy(const Texture2D& texture)
        {
            Update();

            Sampler = texture.Sampler;
            if (texture.Size() != Size())
            {
                Size(texture.Size());
                Update();
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
            Update();

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