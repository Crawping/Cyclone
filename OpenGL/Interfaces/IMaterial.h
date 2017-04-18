/* CHANGELOG
 * Written by Josh Grooms on 20161211
 */

#pragma once
#include "Imaging/Color4.h"
#include "Interfaces/IGraphicsResource.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace OpenGL
    {        
        /** FORWARD DECLARATIONS **/
        class ITexture;


        struct MaterialData : public virtual IResourceData
        {
            /// <summary> The primary color of a material. </summary>
            Color4      PrimaryColor;
            /// <summary> The secondary color of a material. </summary>
            Color4      SecondaryColor;

            ulong       Texture;

            Vector2     _0;

            bool operator ==(const MaterialData& other) const
            {
                return 
                    (Texture == other.Texture)                  &&
                    (PrimaryColor == other.PrimaryColor)        &&
                    (SecondaryColor == other.SecondaryColor);
            }
        };



        /// <summary> An interface used to specify the material properties of an entity. </summary>
        class IMaterial : 
            public virtual IGraphicsResource
        {
            public:

                /// <summary> Gets a structure containing all of the data needed to render the material. </summary>
                //virtual const MaterialData& Data()                  const = 0;
                /// <summary> Gets the primary color of the material. </summary>
                virtual const Color4& PrimaryColor()                const = 0;
                /// <summary> Gets the secondary color of the material. </summary>
                virtual const Color4& SecondaryColor()              const = 0;
                /// <summary> Gets a pointer to the texture used to render the visible surface of a material. </summary>
                /// <remarks>
                ///     Not all materials or material-like entities will have textured associated with them. In those cases, this
                ///     method will return a <c>nullptr</c>.
                /// </remarks>
                virtual const ITexture* Texture()			        const = 0;

                virtual ~IMaterial() { }
        };
    }
}
