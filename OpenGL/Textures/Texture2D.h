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



        class OpenGLAPI Texture2D : public Texture3D
        {

            public:

                /** DATA **/
                /// <summary> A data structure that dictates how the texture is sampled within a GPU shader program. </summary>
                TextureSampler  Sampler;
                /// <summary> A 32-bit RGBA color used to tint the rendered texture. </summary>
                Color4          Tint;



                /** CONSTRUCTOR & DESTRUCTOR **/
                Texture2D(const Vector4& size, TextureFormats format = TextureFormats::Byte4, TextureTargets target = TextureTargets::Texture2D);
                Texture2D(const string& fileName);



                /** UTILITIES **/
                virtual void BindResources()            const override;
                /* COPY - Performs a deep copy operation, replacing all data in this object with those from another texture. */
                void Copy(const Texture2D& texture);

                void CopyFramebuffer(const Area& screenArea, int level = 0);

                Bitmap Read(const Vector3& offset, const Vector2& size)          const;

                virtual string Report()         const;

        };
    }
}
