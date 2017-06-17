/* CHANGELOG
 * Written by Josh Grooms on 20161211
 */

#pragma once
#include "Imaging/Color4.h"
#include "Interfaces/IGraphicsResource.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities { class ISpatialTransform; }

    namespace OpenGL
    {
        /** FORWARD DECLARATIONS **/
        class ITexture;
        template<typename T> struct Resource;
        using namespace Utilities;


        struct MaterialData
        {
            /// <summary> The primary color of a material. </summary>
            Color4      PrimaryColor;
            /// <summary> The secondary color of a material. </summary>
            Color4      SecondaryColor;
            /// <summary> The numeric handle of a material's texture resource on the GPU. </summary>
            ulong       Texture;
            /// <summary> The minimum value of the material's ambient light term during shading. </summary>
            /// <remarks> 
            ///     This parameter is used during shading to determine the uniform lighting across a material and should 
            ///     take on a value between [0.0f, 1.0f].
            /// </remarks>
            float       Ambience;
            /// <summary> The exponent of the material's specular reflection term during shading. </summary>
            /// <remarks> 
            ///     This parameter is used during shading to determine the size of specular light reflections on a material.
            /// </remarks>
            float       SpecularPower;
            /// <summary> A Boolean indicating whether the material is associated with a texture. </summary>
            uint        IsTextured;

            Vector3     _0;

            MaterialData():
                Texture(0),
                Ambience(0.1f),
                SpecularPower(200),
                IsTextured(false)
            {

            }

            bool operator ==(const MaterialData& other) const
            {
                return
                    (Texture == other.Texture)                  &&
                    (PrimaryColor == other.PrimaryColor)        &&
                    (SecondaryColor == other.SecondaryColor);
            }
        };



        /// <summary> An interface used to specify the material properties of an entity. </summary>
        class IMaterial:
            public virtual IGraphicsResource
        {
            public:
                /// <summary> The minimum value of the material's ambient light term during shading. </summary>
                /// <remarks> 
                ///     This parameter is used during shading to determine the uniform lighting across a material and should 
                ///     take on a value between [0.0f, 1.0f].
                /// </remarks>
                virtual float Ambience()                            const = 0;
                /// <summary> Gets a structure containing all of the data needed to render the material. </summary>
                virtual const MaterialData& Data()                  const = 0;
                /// <summary> Gets the primary color of the material. </summary>
                virtual const Color4& PrimaryColor()                const = 0;
                /// <summary> Gets the secondary color of the material. </summary>
                virtual const Color4& SecondaryColor()              const = 0;
                /// <summary> The exponent of the material's specular reflection term during shading. </summary>
                /// <remarks> 
                ///     This parameter is used during shading to determine the size of specular light reflections on a material.
                /// </remarks>
                virtual float SpecularPower()                       const = 0;
                /// <summary> Gets a pointer to the texture used to render the visible surface of a material. </summary>
                /// <remarks>
                ///     Not all materials or material-like entities will have textured associated with them. In those cases, this
                ///     method will return a <c>nullptr</c>.
                /// </remarks>
                //virtual const ITexture* Texture()			        const = 0;
                virtual Resource<ITexture> Texture()                const = 0;

                virtual const ISpatialTransform& Transform()        const = 0;

                virtual ~IMaterial() { }
        };
    }
}
