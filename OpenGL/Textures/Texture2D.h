/* CHANGELOG
 * Written by Josh Grooms on 201509
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"

#include "Imaging/Color4.h"
#include "Math/Vector2.h"
#include "Spatial/Area.h"
#include "Textures/Texture.h"
#include "Textures/TextureSampler.h"

#include <string>



namespace Cyclone
{
    namespace Utilities
    {
        class Bitmap;
        struct Vector3;
    }

    namespace OpenGL
    {
        using namespace Cyclone::Utilities;



        class OpenGLAPI Texture2D : public Texture
        {

            public:

                /** DATA **/
                /* SAMPLER - A data structure that dictates how to sample this texture within a shader program. */
                TextureSampler  Sampler;
                /* TINT - A 32-bit RGBA color that will be used to tint the rendered texture. */
                Color4          Tint;



                /** PROPERTIES **/
                /* HEIGHT - The height in pixels of the texture as it is found on the GPU. */
                uint Height()           const override { return (uint)_size.Y; }
                /* ISEMPTY - Gets whether this texture has any zero-length dimensions. */
                bool IsEmpty()          const override { return Height() == 0 || Width() == 0; }
                /* SIZE - Gets the height and width of the texture as it exists on the GPU. */
                const Vector2& Size()   const { return _size; }
                /* WIDTH - The width in pixels of the texture as it is found on the GPU.
                 *
                 *      This width value ignores any image modifications provided through cropping or padding. It returns the true
                 *      width of the texture from memory.
                 */
                uint Width()            const override { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                Texture2D(TextureFormats format, const Vector2& size = Vector2::Zero);



                /** UTILITIES **/
                /* ALLOCATE - Generates an empty two-dimensional texture of a designated size on the GPU. */
                //void Allocate() override;

                virtual void BindResources()            const override;
                /* COPY - Performs a deep copy operation, replacing all data in this object with those from another texture. */
                void Copy(const Texture2D& texture);

                void CopyFramebuffer(const Area& screenArea, int level = 0);

                Bitmap Read(const Vector3& offset, const Vector2& size)          const;

                virtual string Report()         const;

            protected:
                Vector2     _size;

        };
    }
}
